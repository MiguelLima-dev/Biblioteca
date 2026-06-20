/* Ana Carolina Silva Sousa e Miguel Augusto de Lima
Turma: 14A
Tema: Livros
*/
#include <iostream>
#include <fstream>
using namespace std;
 
// Estrutura utilizada para armazenar as informações de cada livro
struct Livro {
    string titulo;
    int lancamento;
    string autor;
    string genero;
    char sexo; 
    bool ativo = true;
};
 
// Lê um livro do arquivo.
bool leitura(ifstream &arq, Livro &temp) {
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
 
// Particiona o vetor, usando título como comparação.
int particaoTitulo(Livro v[], int inicio, int fim) {
    Livro pivo = v[inicio];
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
// Executa o algoritmo de quick sort para ordenar por título.
void quickSortTitulo(Livro vet[], int esq, int dir) {
    if (esq < dir) {
        int pivo = particaoTitulo(vet, esq, dir);
        quickSortTitulo(vet, esq, pivo - 1);
        quickSortTitulo(vet, pivo + 1, dir);
    }
}
// Executa busca binária, considerando o vetor ordenado por título.
int buscaBinariaTitulo(Livro* v, int inicio, int fim, string procurado) {
    if (inicio > fim) return -1;
    int meio = (inicio + fim) / 2;
    if (procurado == v[meio].titulo) {
        if (v[meio].ativo) return meio;
        else return -1;
    }
    if (procurado > v[meio].titulo) return buscaBinariaTitulo(v, meio + 1, fim, procurado);
    else return buscaBinariaTitulo(v, inicio, meio - 1, procurado);
}

// Particiona o vetor, usando título como comparação.
int particaoAutor (Livro v[], int inicio, int fim){
    Livro pivo = v[inicio];
    int i = inicio + 1, j = fim;
    while (i <= j) {
        if (v[i].autor <= pivo.autor) i++;
        else if (pivo.autor <= v[j].autor) j--;
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
// Executa o algoritmo de quick sort para ordenar por autor.
void quickSortAutor(Livro vet[], int esq, int dir) {
    if (esq < dir) {
        int pivo = particaoAutor(vet, esq, dir);
        quickSortAutor(vet, esq, pivo - 1);
        quickSortAutor(vet, pivo + 1, dir);
    }
}

/* Executa busca binária, considerando o vetor ordenado por autor. Encontra
uma aparição do autor.*/
int buscaBinariaAutor(Livro* v, int inicio, int fim, string procurado) {
    if (inicio > fim) return -1;
    int meio = (inicio + fim) / 2;
    if (v[meio].autor == procurado) {
        if (v[meio].ativo) return meio;
        else return -1;
    }
    if (procurado > v[meio].autor) return buscaBinariaAutor(v, meio + 1, fim, procurado);
    else return buscaBinariaAutor(v, inicio, meio - 1, procurado);
}

/* Toma o índice de um livro, e retorna por referência o intervalo de livros 
do mesmo autor.*/
void expandeAutor(Livro v[], int tam, int meio, int& esq, int& dir) {
    esq = dir = meio;
    while (esq > 0 && v[esq - 1].autor == v[meio].autor) {
        esq--;
    }
    while (dir < tam - 1 && v[dir + 1].autor == v[meio].autor) {
        dir++;
    }
}
// Exibe os livros entre duas posições informadas pelo usuário.
void mostraIntervalo(Livro* v, int tam, int inicio, int fim) {
    if (inicio < 1 || fim > tam || inicio > fim) {
        cout << "Intervalo inválido.\n";
        return;
    }
    for (int i = inicio - 1; i < fim; i++) {
        cout << v[i].titulo << " - " << v[i].autor << " (" << v[i].lancamento << ")\n";
    }
}
 
// Inseri um livro no vetor.
void insercao(Livro* &v, int &tam, int &cap) {
    Livro aux;
    if (tam == cap) {
        Livro* novo = new Livro[cap + 5];
        copy(v, v + cap, novo);
        delete[] v;
        v = novo;
        cap += 5;
    }
    cout << "\n--- Cadastro de novos livros ---\n";
	cout << "Insira o título do novo livro: ";
    getline(cin, aux.titulo);

    cout << "Insira o ano de lançamento da obra: ";
	cin >> aux.lancamento;
	cin.ignore();
	
	cout << "Insira o nome do autor(a): ";
	getline(cin, aux.autor);
	
	cout << "Insira o genero do livro: ";
	getline(cin, aux.genero);
	
	cout << "Insira o sexo do autor(a) (M/F): ";
	cin >> aux.sexo;
    cout << "Livro cadastrado com sucesso!\n";
    
    int i = 0;
    while (i < tam && v[i].titulo < aux.titulo) {
        i++;
    }
    for (int j = tam; j > i; j--) {
        v[j] = v[j - 1];
    }
    v[i] = aux;
    tam++;
}

// Removi logicamente um livro do vetor.
void remover(Livro v[], int tam, string titulo) {
    int indice = buscaBinariaTitulo(v, 0, tam - 1, titulo);
    if (indice != -1) {
        v[indice].ativo = false;
        cout << "Livro removido com sucesso!\n";
    }
    else {
        cout << "Livro não encontrado.\n";
    }
}

void salvar(ofstream &arq, Livro v[], int tam) {
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
    Livro* vetor = new Livro[capac];
 
    int tam = 0; // Quantos livros foram inseridos.
    
    // Descarta o cabeçalho.
    string descarte;
    getline(planilha, descarte);
    
    Livro temp;
    while(leitura(planilha, temp)){ 
        /* Julga se o redimensionamento do vetor é necessário, caso
        seja, aumenta o vetor em cinco espaços.*/
        if (tam == capac) {
            Livro* novo = new Livro[capac + 5];
            copy(vetor, vetor + tam, novo);
            delete[] vetor;
            vetor = novo;
            capac += 5;
        }
        
        vetor[tam] = temp;
        tam++;
    }
    planilha.close();

    /* Menu principal. O usuário escolhe a operação desejada e o programa
    executa até que a opção de saída seja escolhida. */
    int opcao;
    do {
        cout << "\n--- Biblioteca ---\n";
        cout << "1 - Buscar por titulo\n";
        cout << "2 - Buscar por autor\n";
        cout << "3 - Mostrar intervalo\n";
        cout << "4 - Inserir obra\n";
        cout << "5 - Remover obra\n";
        cout << "6 - Salvar mudanças\n";
        cout << "0 - Sair\n";
        cout << "Opcao: ";
        cin >> opcao;
        cin.ignore();

        switch (opcao) {
            case 1: {
                string procura;
                cout << "Insira um título: ";
                getline(cin, procura);

                quickSortTitulo(vetor, 0, tam - 1);
                int index = buscaBinariaTitulo(vetor, 0, tam - 1, procura);
                if (index == -1) cout << "Título não encontrado.\n";
                else cout << vetor[index].autor << endl;
                break;
            }
            case 2: {
                string procura;
                cout << "insira um autor: ";
                getline(cin, procura);
                quickSortAutor(vetor, 0, tam - 1);
                int index = buscaBinariaAutor(vetor, 0, tam - 1, procura);
                if (index == -1) cout << "Nenhum livro desse autor encotrado.\n";
                else {
                    int esq, dir;
                    expandeAutor(vetor, tam, index, esq, dir);
                    cout << "Livros de " << procura << " encontrados:\n";
                    for (int i = esq; i <= dir; i++) {
                        cout << "--" << vetor[i].titulo << "--\n";
                    }
                }
                break;
            }
            
            case 3: {
                int ini, fim;
                cout << "Insira o início do intervalo: ";
                cin >> ini;
                cout << "Insira o fim do intervalo: ";
                cin >> fim;
                mostraIntervalo(vetor, tam, ini, fim);
                break;
            }
        
            case 4: {
                insercao(vetor, tam, capac);
                break;
            }
            case 5: {
                quickSortTitulo(vetor, 0 , tam - 1);
                string removendo;
                cout << "Insira o título da obra que deseja remover: ";
                getline(cin, removendo);
                remover(vetor, tam, removendo);
                break;
            }
            case 6: {
                ofstream saida ("biblioteca.csv");
                salvar(saida, vetor, tam);
                saida.close();
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