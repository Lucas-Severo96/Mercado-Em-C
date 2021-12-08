#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

typedef struct {
	int codigo;
	char nome[30];
	float preco;
} Produto;

typedef struct {
	Produto produto;
	int quantidade;
} Carrinho;

void infoProduto(Produto prod);
void menu();
void cadastrarProduto();
void listarProdutos();
void comprarProduto();
void visualizarCarrinho();
Produto pegarProdutoPorCodigo(int codigo);
int * temNoCarrinho(int codigo);
void fecharPedido();

static int contadorProduto = 0;
static int contadorCarrinho = 0;
static Carrinho carrinho[50];
static Produto produtos[50];

int main() {

	menu();
	return 0;
}


void infoProduto(Produto prod) {
	printf("Código: %d \nNome: %s \nPreço: %.2f \n", prod.codigo, strtok(prod.nome,"\n"), prod.preco);
}

void menu() {
	printf("======================================\n");
	printf("============ Bem-Vindo(a) ============\n");
	printf("============== C Shop ================\n ");
	printf("======================================\n");

	printf("Selecione uma opção abaixo: \n");
	printf("1 - Cadastrar Produto\n");
	printf("2 - Listar Produto(s)\n");
	printf("3 - Comprar Produto\n");
	printf("4 - Visualizar Carrinho\n");
	printf("5 - Fechar Pedido\n");
	printf("6 - Sair do Sistema\n");

	int opcao;
	fflush(stdout);
	scanf("%d", &opcao);
	getchar();

	switch (opcao) {
		case 1:
			cadastrarProduto();
			break;
		case 2:
			listarProdutos();
			break;
		case 3:
			comprarProduto();
			break;
		case 4:
			visualizarCarrinho();
			break;
		case 5:
			fecharPedido();
			break;
		case 6:
			printf("VOLTE SEMPRE. OBRIGADO(A)!\n");
			Sleep(2);
			exit(0);
		default:
			printf("OPÇAO INVÁLIDA!!\n");
			Sleep(2);
			menu();
			break;
	}
}

void cadastrarProduto() {
	printf("Cadastro de Produto\n");
	printf("====================\n");

	printf("Informe o nome do Produto: \n");
	fgets(produtos[contadorProduto].nome, 30, stdin);

	printf("Informe o preço do produto: \n");
	fflush(stdout);
	scanf("%f", &produtos[contadorProduto].preco);

	printf("O produto foi cadastrado com Sucesso!\n", strtok(produtos[contadorProduto].nome, "\n"));

	produtos[contadorProduto].codigo = (contadorProduto + 1);
	contadorProduto++;
}
void listarProdutos() {
	if(contadorProduto > 0) {
		printf("Listagem de Produtos.\n");
		printf("---------------------\n");
		for(int i = 0; i < contadorProduto; i++) {
			infoProduto(produtos[i]);
			printf("-----------------\n");
			Sleep(1);

		}
	}else {
		printf("Não temos ainda produtos cadastrados.\n");
	}
}

void comprarProduto() {

}
void visualizarCarrinho() {
	if(contadorCarrinho > 0) {
		printf("Produtos do Carrinho\n");
		printf("---------------------\n");
		for(int i = 0; i < contadorCarrinho; i++) {
			printf("Quantidade: %d\n", carrinho[i].quantidade);
			printf("---------------\n");
			Sleep(1);
		}

	}else {
		printf("Não temos ainda produtos no carrinho!\n");
	}
}
Produto pegarProdutoPorCodigo(int codigo) {
	Produto p;
	for(int i = 0; i < contadorProduto; i++) {
		if(produtos[i].codigo == codigo) {
			p = produtos[i];
		}
	}
	return p;
}
int * temNoCarrinho(int codigo) {
	int static retorno[] = (0,0);
	for(int i = 0; i < contadorCarrinho; i++) {
		if(carrinho[i].produto.codigo == codigo) {
			retorno[0] = 1; //Tem o produto com este código no carrinho
			retorno[1] = i; //Índice do produto no Carrinho (i)
		}
	}
	return retorno;
}
void fecharPedido() {
	if(contadorCarrinho > 0) {
		float valorTotal = 0.0;
		printf("Produtos do Carrinho\n");
		printf("--------------------\n");
		for(int i = 0; i < contadorCarrinho; i++) {
			Produto p = carrinho[i].produto;
			int quantidade = carrinho[i].quantidade;
			valorTotal += p.preco * quantidade;
			infoProduto(p);
			printf("Quantidade: %d\n", quantidade);
			printf("---------------\n");
			Sleep(1);
		}
		printf("Sua fatura é R$ %.2f\n", valorTotal);

		//Limpando o Carrinho
		contadorCarrinho = 0;
		printf("OBRIGADO PELA PREFERÊNCIA.\n");
		Sleep(5);
		menu();

	}else {
		printf("Você não tem nenhum produto no carrinho ainda!\n");
		Sleep(3);
		menu();
	}
}
