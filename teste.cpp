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
 bool leitura(ifstream &arq, livro* vetor, int &indice) {
    if (!getline(arq, vetor[indice].titulo, ','))
        return false;

    if (!arq >> vetor[indice].lancamento)
        return false;
    
    char virgula; // Variável para o descarte da vírgula.
    if (!arq >> virgula)
        return false;

    if(!getline(arq, vetor[indice].autor, ','))
        return false;

    if(!getline(arq, vetor[indice].genero, ','))
        return false;

    if (!arq >> vetor[indice].sexo)
        return false;
    arq.ignore();

    indice++;
    return true;
}

int main(){
    ifstream planilha("biblioteca.csv");

    if (!planilha) {
        cout << "Erro ao abrir o arquivo.\n";
    }

    int capac = 40; // Quantas posiçoes o vetor guarda.
    livro* vetor = new livro[capac];

    char virgula; // Variável para descarte da vírgula.
    int ocupados = 0; // Quantos livros foram inseridos.
    while(leitura(planilha, vetor, ocupados)){   
        if (ocupados == capac) { // Redimensiona o vetor. 
            livro* novo = new livro[capac + 5];
            for (int i = 0; i < capac; i++) {
                novo[i] = vetor[i];
            }
            delete[] vetor;
            vetor = novo;
            capac += 5;
        }
    }
    planilha.close();

    delete[] vetor;
    return 0;
}