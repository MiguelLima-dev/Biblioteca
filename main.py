import csv

class Livro:
	"""Estrutura de um livro, guarda:
	Título, Ano de Lançamento, Autor, Gênero e Sexo do autor"""
	def __init__(self, titulo="", ano=0, autor="", genero="", sexo="", ativo=True):
		self.titulo = titulo
		self.ano = ano
		self.autor = autor
		self.genero = genero
		self.sexo = sexo
		
		# Variável para remoção lógica.
		self.ativo = ativo
	
	def Del(self):
		self.ativo = False
	
	def __str__(self):
		return f"{self.titulo} escrito por: {self.autor}\nPublicado em {self.ano}\nGênero: {self.genero}"


def LerArquivo(nomeArquivo):
	try:
		with open(nomeArquivo, mode='r', encoding='utf-8') as fin:
			leitor = csv.reader(fin)
			next(leitor, None)  # Descarta cabeçalho
			livros = []
			for line in leitor:
				if len(line) >= 5:
					livro = Livro(
						titulo=line[0].strip(),
						ano=int(line[1].strip()),
						autor=line[2].strip(),
						genero=line[3].strip(),
						sexo=line[4].strip()
					)
					livros.append(livro)
			return livros, len(livros)
	except FileNotFoundError:
		print("Erro ao abrir o arquivo.")
		return None, 0


def ParticaoTitulo(v, inicio, fim):
	pivo = v[inicio]
	i = inicio + 1
	j = fim
	
	while i <= j:
		if v[i].titulo <= pivo.titulo:
			i += 1
		elif v[j].titulo >= pivo.titulo:
			j -= 1
		else:
			v[i], v[j] = v[j], v[i]
			i += 1
			j -= 1
			
	v[inicio], v[j] = v[j], v[inicio]
	return j


def QuickSortTitulo(v, left, right):
	if left < right:
		pivo = ParticaoTitulo(v, left, right)
		QuickSortTitulo(v, left, pivo - 1)
		QuickSortTitulo(v, pivo + 1, right)

	
def BuscaBinariaTitulo(v, inicio, fim, procurado):
	if inicio > fim:
		return -1
	meio = (inicio + fim) // 2
	if procurado == v[meio].titulo:
		if v[meio].ativo:
			return meio
		return -1
	if procurado > v[meio].titulo:
		return BuscaBinariaTitulo(v, meio + 1, fim, procurado)
	return BuscaBinariaTitulo(v, inicio, meio - 1, procurado)


def ParticaoAutor(v, inicio, fim):
	pivo = v[inicio]
	i = inicio + 1
	j = fim
	
	while i <= j:
		if v[i].autor <= pivo.autor:
			i += 1
		elif v[j].autor >= pivo.autor:
			j -= 1
		else:
			v[i], v[j] = v[j], v[i]
			i += 1
			j -= 1
	
	v[inicio], v[j] = v[j], v[inicio]
	return j


def QuickSortAutor(v, left, right):
	if left < right:
		pivo = ParticaoAutor(v, left, right)
		QuickSortAutor(v, left, pivo - 1)
		QuickSortAutor(v, pivo + 1, right)

		
def BuscaBinariaAutor(v, inicio, fim, procurado):
    if inicio > fim:
        return -1
    meio = (inicio + fim) // 2
    if v[meio].autor == procurado:
        return meio
    if procurado > v[meio].autor:
        return BuscaBinariaAutor(v, meio + 1, fim, procurado)
    else:
        return BuscaBinariaAutor(v, inicio, meio - 1, procurado)


def expande_autor(v, tam, meio):
    esq = meio
    dir = meio
    while esq > 0 and v[esq - 1].autor == v[meio].autor:
        esq -= 1
    while dir < tam - 1 and v[dir + 1].autor == v[meio].autor:
        dir += 1
    return esq, dir

  
def mostra_intervalo(v, tam, inicio, fim):
    if inicio < 1 or fim > tam or inicio > fim:
        print("Intervalo inválido.")
        return
    for i in range(inicio - 1, fim):
        if v[i].ativo:
            print("----------------------------------------")
            print(v[i])  # Utiliza o __str__ da instância[cite: 5]
            print("----------------------------------------")

            
def insercao(v, ordem):
    aux = Livro()
    print("\n--- Cadastro de novos livros ---")
    aux.titulo = input("Insira o título do novo livro: ")
    aux.ano = int(input("Insira o ano de lançamento da obra: "))
    aux.autor = input("Insira o nome do autor(a): ")
    aux.genero = input("Insira o genero do livro: ")
    aux.sexo = input("Insira o sexo do autor(a) (M/F): ")
    print("Livro cadastrado com sucesso!")

    i = len(v) - 1
    v.append(None)  # Abre espaço para o novo elemento

    if ordem == "titulo":
        while i >= 0 and v[i].titulo > aux.titulo:
            v[i + 1] = v[i]
            i -= 1
        v[i + 1] = aux
    elif ordem == "autor":
        while i >= 0 and v[i].autor > aux.autor:
            v[i + 1] = v[i]
            i -= 1
        v[i + 1] = aux
    else:
        v[-1] = aux          


def remover(v, tam, titulo):
    indice = BuscaBinariaTitulo(v, 0, tam - 1, titulo)
    if indice != -1:
        v[indice].Del()
        print("Livro removido com sucesso!")
        return True
    else:
        print("Livro não encontrado.")
        return False


# Salva no arquivo os dados após a manipulação do programa
def salvar(nome_arquivo, v):
    with open(nome_arquivo, mode='w', encoding='utf-8', newline='') as arq:
        escritor = csv.writer(arq, quoting=csv.QUOTE_MINIMAL)
        escritor.writerow(["Título", "Lançamento", "Autor", "Gênero", "Sexo"])
        for livro in v:
            if livro.ativo:
                escritor.writerow([livro.titulo, livro.ano, livro.autor, livro.genero, livro.sexo])


def main():
    vetor, tam = LerArquivo("biblioteca.csv")
    if vetor is None:
        return

    livros_ativos = tam
    ordenacao = "nenhuma"

    while True:
        print("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=")
        print(f"Existem {livros_ativos} livros no acervo.")
        print("=-=-=-=-= Biblioteca =-=-=-=-=")
        print("1 - Buscar por título")
        print("2 - Ordenar por título")
        print("3 - Buscar por autor")
        print("4 - Ordenar por autor")
        print("5 - Mostrar intervalo")
        print("6 - Mostrar todos livros")
        print("7 - Inserir obra")
        print("8 - Remover obra")
        print("9 - Salvar mudanças")
        print("0 - Sair")
        print("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=")
        opcao = input("Opcao: ").strip()

        tam = len(vetor)

        if opcao == '1':
            procura = input("Insira um título: ")
            if ordenacao != "titulo":
                QuickSortTitulo(vetor, 0, tam - 1)
            index = BuscaBinariaTitulo(vetor, 0, tam - 1, procura)
            if index == -1:
                print("Título não encontrado.")
            else:
                print("\nLivro encontrado:")
                print(vetor[index])  # Usa o __str__ da instância[cite: 5]

            if ordenacao == "autor":
                QuickSortAutor(vetor, 0, tam - 1)

        elif opcao == '2':
            QuickSortTitulo(vetor, 0, tam - 1)
            ordenacao = "titulo"
            print("Vetor ordenado por título.")

        elif opcao == '3':
            procura = input("Insira um autor: ")
            if ordenacao != "autor":
                QuickSortAutor(vetor, 0, tam - 1)
            index = BuscaBinariaAutor(vetor, 0, tam - 1, procura)
            if index == -1:
                print("Nenhum livro desse autor encontrado.")
            else:
                esq, dir = expande_autor(vetor, tam, index)
                achou_ativo = False
                for i in range(esq, dir + 1):
                    if vetor[i].ativo:
                        if not achou_ativo:
                            print(f"\nLivros de {procura} encontrados:")
                            achou_ativo = True
                        print("----------------------------------------")
                        print(vetor[i])  # Usa o __str__ da instância[cite: 5]
                if not achou_ativo:
                    print("Nenhum livro desse autor encontrado.")

            if ordenacao == "titulo":
                QuickSortTitulo(vetor, 0, tam - 1)

        elif opcao == '4':
            QuickSortAutor(vetor, 0, tam - 1)
            ordenacao = "autor"
            print("Vetor ordenado por autor.")

        elif opcao == '5':
            ini = int(input("Insira o início do intervalo: "))
            fim = int(input("Insira o fim do intervalo: "))
            mostra_intervalo(vetor, tam, ini, fim)

        elif opcao == '6':
            mostra_intervalo(vetor, tam, 1, tam)

        elif opcao == '7':
            insercao(vetor, ordenacao)
            livros_ativos += 1

        elif opcao == '8':
            if ordenacao != "titulo":
                QuickSortTitulo(vetor, 0, tam - 1)
            removendo = input("Insira o título da obra que deseja remover: ")
            if remover(vetor, tam, removendo):
                livros_ativos -= 1

            if ordenacao == "autor":
                QuickSortAutor(vetor, 0, tam - 1)

        elif opcao == '9':
            salvar("biblioteca.csv", vetor)

        elif opcao == '0':
            print("Encerrando.")
            break
        else:
            print("Opção inválida.")

        print()


if __name__ == "__main__":
    main()
