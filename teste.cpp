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
 bool leitura(ifstream &arq, livro temp) {
    if (!getline(arq, temp.titulo, ','))
        return false;

    if (!arq >> temp.lancamento)
        return false;
    
    char virgula; // Variável para o descarte da vírgula.
    if (!arq >> virgula)
        return false;

    if(!getline(arq, temp.autor, ','))
        return false;

    if(!getline(arq, temp.genero, ','))
        return false;

    if (!arq >> temp.sexo)
        return false;
    arq.ignore();

    return true;
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
        vetor[ocupados++] = temp;
        
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