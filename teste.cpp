#include <iostream>
#include <fstream>
using namespace std;

struct livro {
    string titulo;
    int lancamento;
    string autor;
    string genero;
    char sexo; 
};

int main(){
    ifstream bancoDados("biblioteca.csv");
    ofstream saida("saida.txt");
    livro biblioteca[40];

    char virgula;
    for (int i = 0; i < 1; i++){
        getline(bancoDados, biblioteca[i].titulo, ',');
        
        bancoDados >> biblioteca[i].lancamento;
        bancoDados >> virgula;

        getline(bancoDados, biblioteca[i].autor, ',');

        getline(bancoDados, biblioteca[i].genero, ',');

        bancoDados >> biblioteca[i].sexo;
        bancoDados.ignore();
    }
    bancoDados.close();

    for (int i = 0; i < 1; i++){
        saida << biblioteca[i].titulo;
        saida << biblioteca[i].lancamento;
        saida << biblioteca[i].autor;
        saida << biblioteca[i].genero;
        saida << biblioteca[i].sexo;
    }
    saida.close();

    return 0;
}