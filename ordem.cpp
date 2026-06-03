#include <iostream> 
#include <fstream>
using namespace std;

/* Código que resolve aquele problema do coding dojo, de ler "Tam" números
e inserir eles em um vetor em ordem crescente. Dá pra usar esse algoritmo na hora
de carregar os Livros na memória.
*/

int main(){
    ifstream entrada("entrada.txt");

    int tam;
    entrada >> tam;
    int* v = new int[tam];

    int ocupados = 0;
    for (int i = 0; i < tam; i++) {
        int num;
        entrada >> num;
        if (i == 0)
            v[ocupados] = num;
        else {
            int j = 0;
            while (j < ocupados && num > v[j])
                j++;
            for (int k = ocupados; k > j; k--)
                v[k] = v[k - 1];
            v[j] = num;
        }

        ocupados++;
    }

    for (int i = 0; i < tam; i++)
        cout << v[i] << " ";

    cout << endl;
    entrada.close();
    delete[] v;
    return 0;
}