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
 
// Executa busca binária, considerando o vetor ordenado por título.
int buscaBinaria(livro* v, int inicio, int fim, string procurado) {
    if (inicio > fim) return -1;
    int meio = (inicio + fim) / 2;
    if (procurado == v[meio].titulo) return meio;
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
 
int main(){
    ifstream planilha("biblioteca.csv");
 
    if (!planilha) {
        cout << "Erro ao abrir o arquivo.\n";
        return 1;
    }
 
    int capac = 40; // Quantas posiçoes o vetor guarda.
    livro* vetor = new livro[capac];
 
    int ocupados = 0; // Quantos livros foram inseridos.
    
    livro temp;
    while(leitura(planilha, temp)){ 
        /* Julga se o redimensionamento do vetor é necessário, caso
        seja, aumenta o vetor em cinco espaços.*/
        if (ocupados == capac) {
            livro* novo = new livro[capac + 5];
            for (int i = 0; i < capac; i++) {
                novo[i] = vetor[i];
            }
            delete[] vetor;
            vetor = novo;
            capac += 5;
        }
 
        /* Insere os livro no vetor, já ordenados por título. A comparação utilizada
        é o código ASCII(padrão na comparação de strings em C++)*/ 
        if (ocupados == 0)
            vetor[0] = temp;
        else {
            int j = 0;
            while (j < ocupados && temp.titulo > vetor[j].titulo)
                j++;
            for (int k = ocupados; k > j; k--)
                vetor[k] = vetor[k - 1];
            vetor[j] = temp;
        }
        ocupados++;
    }
    planilha.close();
 
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
 
