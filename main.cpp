/* Ana Carolina Silva Sousa, Maria Clara, Miguel Augusto de Lima
Turma: 14A
Tema: Livros
*/
#include <iostream>
#include <fstream>
using namespace std;
 
// Estrutura utilizada para armazenar as informações de cada livro
struct livro {
    string titulo;
    int lancamento;
    string autor;
    string genero;
    char sexo; 
    bool ativo = true;
};
 
// Lê um livro do arquivo.
bool leitura(ifstream &arq, livro &temp) {
    char aspa; // Variável para o descarte da aspa.
    char virgula; // Variável para o descarte da vírgula.

    if (!(arq >> aspa)) return false;
    if (!getline(arq, temp.titulo, '"')) return false;
    if (!(arq >> virgula)) return false;
    if (!(arq >> temp.lancamento)) return false;
    if (!(arq >> virgula)) return false;
    if(!getline(arq, temp.autor, ',')) return false;
    if(!getline(arq, temp.genero, ',')) return false;
    if (!(arq >> temp.sexo)) return false;
    arq.ignore();
 
    return true;
}
 
// Ordena os livros por título.
// Particiona o vetor.
int particao(livro v[], int inicio, int fim) {
    livro pivo = v[inicio];
    int i = inicio + 1, j = fim;
    while (i <= j) {
        if (v[i].titulo <= pivo.titulo) i++;
        else if (pivo.titulo <= v[j].titulo) j--;
        else {
            swap(v[i], v[j]);
            i++;
            j--;
        }
    }
    v[inicio] = v[j];
    v[j] = pivo;
    return j;
}
// Executa o algoritmo de quick sort.
void quickSort(livro vet[], int esq, int dir) {
    if (esq < dir) {
        int pivo = particao(vet, esq, dir);
        quickSort(vet, esq, pivo - 1);
        quickSort(vet, pivo + 1, dir);
    }
}
// Executa busca binária, considerando o vetor ordenado por título.
int buscaBinaria(livro* v, int inicio, int fim, string procurado) {
    if (inicio > fim) return -1;
    int meio = (inicio + fim) / 2;
    if (procurado == v[meio].titulo) {
        if (v[meio].ativo) return meio;
        else return -1;
    }
    if (procurado > v[meio].titulo) return buscaBinaria(v, meio + 1, fim, procurado);
    else return buscaBinaria(v, inicio, meio - 1, procurado);
}
 
// Exibe todos os títulos de um determinado autor.
void buscaAutor(livro* v, int ocupados, string procurado) {
    bool encontrou = false;
    for (int i = 0; i < ocupados; i++) {
        if (v[i].autor == procurado) {
            cout << v[i].titulo << endl;
            encontrou = true;
        }
    }
    if (!encontrou)
        cout << "Autor não encontrado.\n";
}
 
// Exibe todos os títulos de um determinado gênero.
void buscaGenero(livro* v, int ocupados, string procurado) {
    bool encontrou = false;
    for (int i = 0; i < ocupados; i++) {
        if (v[i].genero == procurado) {
            cout << v[i].titulo << endl;
            encontrou = true;
        }
    }
    if (!encontrou)
        cout << "Gênero não encontrado.\n";
}
 
// Exibe todos os títulos de acordo com o sexo do autor (M ou F).
void buscaSexo(livro* v, int ocupados, char procurado) {
    bool encontrou = false;
    for (int i = 0; i < ocupados; i++) {
        if (v[i].sexo == procurado) {
            cout << v[i].titulo << endl;
            encontrou = true;
        }
    }
    if (!encontrou)
        cout << "Nenhum livro encontrado.\n";
}
 
// Exibe todos os títulos lançados em um determinado ano.
void buscaAno(livro* v, int ocupados, int procurado) {
    bool encontrou = false;
    for (int i = 0; i < ocupados; i++) {
        if (v[i].lancamento == procurado) {
            cout << v[i].titulo << endl;
            encontrou = true;
        }
    }
    if (!encontrou)
        cout << "Ano não encontrado.\n";
}
 
// Exibe os livros entre duas posições informadas pelo usuário.
void mostraIntervalo(livro* v, int ocupados, int inicio, int fim) {
    if (inicio < 1 || fim > ocupados || inicio > fim) {
        cout << "Intervalo inválido.\n";
        return;
    }
    for (int i = inicio - 1; i < fim; i++) {
        cout << v[i].titulo << " - " << v[i].autor << " (" << v[i].lancamento << ")\n";
    }
}
 
// Inseri um livro no vetor.
void insercao(livro* &v, int &tam, int &cap) {
    if (tam == cap) {
        livro* novo = new livro[cap + 1];
        copy(v, v + cap, novo);
        delete[] v;
        v = novo;
        cap++;
    }
    cout << "\n--- Cadastro de novos livros ---\n";
	cout << "Insira o título do novo livro: ";
    getline(cin, v[tam].titulo);

    cout << "Insira o ano de lançamento da obra: ";
	cin >> v[tam].lancamento;
	cin.ignore();
	
	cout << "Insira o nome do autor(a): ";
	getline(cin, v[tam].autor);
	
	cout << "Insira o genero do livro: ";
	getline(cin, v[tam].genero);
	
	cout << "Insira o sexo do autor(a) (M/F): ";
	cin >> v[tam].sexo;
    cout << "Livro cadastrado com sucesso!\n";
    
    tam++;
    quickSort(v, 0, tam - 1);
}

// Removi logicamente um livro do vetor.
void deletar(livro v[], int tam, string titulo) {
    int indice = buscaBinaria(v, 0, tam - 1, titulo);
    if (indice != -1) {
        v[indice].ativo = false;
        cout << "Livro removido com sucesso!\n";
    }
}

void salvar(ofstream &arq,livro v[], int tam) {
    for (int i = 0; i < tam; i++) {
        if (v[i].ativo) {
        arq << "\"" << v[i].titulo << "\"" << "," <<
        v[i].lancamento << "," << v[i].autor << "," <<
        v[i].genero << "," << v[i].sexo << endl;
        }
    }
}

int main(){
    ifstream planilha("biblioteca.csv");
 
    if (!planilha) {
        cout << "Erro ao abrir o arquivo.\n";
        return 1;
    }
 
    int capac = 40; // Quantas posiçoes o vetor guarda.
    livro* vetor = new livro[capac];
 
    int ocupados = 0; // Quantos livros foram inseridos.
    
    // Descarta o cabeçalho.
    string descarte;
    getline(planilha, descarte);
    
    livro temp;
    while(leitura(planilha, temp)){ 
        /* Julga se o redimensionamento do vetor é necessário, caso
        seja, aumenta o vetor em cinco espaços.*/
        if (ocupados == capac) {
            livro* novo = new livro[capac + 5];
            copy(vetor, vetor + ocupados, novo);
            delete[] vetor;
            vetor = novo;
            capac += 5;
        }
        
        vetor[ocupados] = temp;
        ocupados++;
    }
    planilha.close();
 
    quickSort(vetor, 0, ocupados - 1);

    /* Menu principal. O usuário escolhe a operação desejada e o programa
    executa até que a opção de saída seja escolhida. */
    int opcao;
    do {
        cout << "\n--- Biblioteca ---\n";
        cout << "1 - Buscar por titulo\n";
        cout << "2 - Buscar por autor\n";
        cout << "3 - Buscar por genero\n";
        cout << "4 - Buscar por sexo do autor\n";
        cout << "5 - Buscar por ano\n";
        cout << "6 - Mostrar intervalo\n";
        cout << "0 - Sair\n";
        cout << "Opcao: ";
        cin >> opcao;
        cin.ignore();

        switch (opcao) {
            case 1: {
                string procura;
                cout << "Insira um título: ";
                getline(cin, procura);
                int index = buscaBinaria(vetor, 0, ocupados - 1, procura);
                if (index == -1) cout << "Título não encontrado.\n";
                else cout << vetor[index].autor << endl;
                break;
            }
            case 2: {
                string procuraAutor;
                cout << "Insira um autor: ";
                getline(cin, procuraAutor);
                buscaAutor(vetor, ocupados, procuraAutor);
                break;
            }
            case 3: {
                string procuraGenero;
                cout << "Insira um gênero: ";
                getline(cin, procuraGenero);
                buscaGenero(vetor, ocupados, procuraGenero);
                break;
            }
            case 4: {
                char procuraSexo;
                cout << "Insira o sexo do autor (M/F): ";
                cin >> procuraSexo;
                buscaSexo(vetor, ocupados, procuraSexo);
                break;
            }
            case 5: {
                int procuraAno;
                cout << "Insira um ano: ";
                cin >> procuraAno;
                buscaAno(vetor, ocupados, procuraAno);
                break;
            }
            case 6: {
                int ini, fim;
                cout << "Insira o início do intervalo: ";
                cin >> ini;
                cout << "Insira o fim do intervalo: ";
                cin >> fim;
                mostraIntervalo(vetor, ocupados, ini, fim);
                break;
            }
            case 0:
                cout << "Encerrando.\n";
                break;
            default:
                cout << "Opção inválida.\n";
        }
    } while (opcao != 0);

    delete[] vetor;
    return 0;
}