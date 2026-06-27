# Sistema de Cadastro de Acervo Literário com Ordenação (C++)

Este projeto consiste em um sistema de gerenciamento e cadastro de obras literárias (livros) desenvolvido em C++. A aplicação foi projetada para rodar em ambiente Linux genérico e utiliza conceitos de manipulação de arquivos CSV, alocação dinâmica de memória, algoritmos de ordenação eficientes ($O(n \log n)$) e busca binária ($O(\log n)$).

O tema escolhido para a base de dados foi Livros, abrangendo grandes clássicos da literatura mundial e gêneros variados como romance, poesia, ficção científica e terror.

---

## Funcionalidades

O sistema oferece um menu interativo com as seguintes operações:
1. **Buscar por título:** Realiza busca binária pelo título da obra. (A ordenação é feita temporariamente para a busca e o estado anterior do vetor é restaurado ao final).
2. **Ordenar por título:** Ordena permanentemente o vetor em memória por ordem alfabética de títulos usando o algoritmo QuickSort.
3. **Buscar por autor:** Realiza busca binária por autor. Retorna múltiplos livros do mesmo escritor utilizando um algoritmo de expansão bidirecional.
4. **Ordenar por autor:** Ordena permanentemente o vetor em memória por ordem alfabética de autores usando QuickSort.
5. **Mostrar intervalo:** Exibe os livros contidos em um intervalo específico de posições informado pelo usuário (ex: do 10º ao 20º elemento).
6. **Mostrar todos os livros:** Exibe na tela todos os registros ativos carregados na memória.
7. **Inserir obra:** Registra um novo livro. Se o acervo já estiver ordenado, o elemento é inserido na posição correta via deslocamento, preservando a ordenação.
8. **Remover obra:** Realiza a remoção lógica de uma obra alterando sua flag de estado para inativa.
9. **Salvar mudanças:** Reescreve o arquivo `biblioteca.csv`, realizando a remoção física definitiva dos registros marcados como inativos.
0. **Sair:** Encerra o programa e desaloca toda a memória utilizada.

---

## Detalhes Técnicos e Estruturas

* **Vetor Dinâmico Manual:** Os dados são carregados inicialmente do arquivo CSV para um vetor alocado dinamicamente com capacidade inicial de 40 elementos. Sempre que o vetor atinge o seu limite, ele é expandido manualmente em blocos de 5 novas posições.
* **Estrutura Heterogênea (`struct`):** Cada registro armazena `titulo` (string com espaços), `lancamento` (inteiro), `autor` (string), `genero` (string), `sexo` (char) e `ativo` (bool).
* **Restrições Vigentes:** O código foi desenvolvido estritamente sem o uso da biblioteca `<vector>` ou funções prontas de ordenação (como `std::sort`), utilizando algoritmos manuais para comprovar o domínio de alocação e ordenação. Não há uso de variáveis globais ou comandos proibidos como `goto`.

---

## Estrutura do Arquivo de Dados (`biblioteca.csv`)

O arquivo de dados utiliza a vírgula (`,`) como delimitador de campo. O título é delimitado por aspas duplas (`" "`) para suportar títulos que contenham vírgulas e pontuações internas:
```csv
Título,Lançamento,Autor,Gênero,Sexo
"A Carne",1888,Júlio Ribeiro,Romance,M
"O Leão, a Feiticeira e o Guarda-Roupa",1950,C. S. Lewis,Fantasia,M
"2001: Uma Odisseia no Espaço",1968,Arthur C. Clarke,Ficção Científica,M
