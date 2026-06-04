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
/* A leitura precisa que nenhum campo contenha vírgula, seria
bom tratar isso.*/
 bool leitura(ifstream &arq, livro &temp) {
    if (!getline(arq, temp.titulo, ','))
        return false;

    if (!(arq >> temp.lancamento))
        return false;
    
    char virgula; // Variável para o descarte da vírgula.
    if (!arq.get(virgula)) // OLHAR ISSO AQUI.
        return false;

    if(!getline(arq, temp.autor, ','))
        return false;

    if(!getline(arq, temp.genero, ','))
        return false;

    if (!(arq >> temp.sexo))
        return false;
    arq.ignore();

    return true;
}

// Executa busca binária, considerando o vetor ordenado por título.
int buscaBinaria(livro* v, int inicio, int fim, string procurado) {
    if (inicio > final) return -1;
    int meio = (inicio + final) / 2;
    if (procurado == v[meio].titulo) return meio;
    if (procurado > v[meio].titulo) return buscaBinaria(v, meio + 1, fim, procurado);
    else return buscaBinaria(v, inicio, meio - 1, procurado);
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

    /* Toma como entrada um título e exibe qual o autor.*/
    string procura;
    cout << "Insira um título: ";
    getline(cin, procura);
    int index = buscaBinaria(vetor, 0, ocupados - 1, procura);
    if (index == -1) cout << "Título não encontrado.\n";
    else cout << vetor[index].autor << endl;

    delete[] vetor;
    return 0;
}
