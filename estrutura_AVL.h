#ifndef ARVORE_AVL
#define ARVORE_AVL

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>

typedef struct Fornecedor
{
    int codigo;
    char nome[100];
    char telefone[20];
}Fornecedor;

typedef struct Estoque
{
    int codigoProduto;
    int quantidade;
}Estoque;

typedef struct Produto
{
    int codigo;
    char nome[100];
    Fornecedor *fornecedor;
    Estoque *estoque;
}Produto;

typedef struct NoAVL
{
    Produto produto;
    int altura;
    struct NoAVL *esq;
    struct NoAVL *dir;
}NoAVL;

NoAVL *buscarProduto(NoAVL *raiz, int codigoProduto);

int buscarComPassos(NoAVL *raiz, int codigoProduto, int *passos);

int cadastrarEstoque(NoAVL *raiz, int codigoProduto, int quantidade);

void mostrarProduto(NoAVL *raiz, int codigoProduto);

NoAVL *criarNoAVL(Produto produto);

void inserirAVL(NoAVL **raiz, NoAVL *novo);

int altura(NoAVL *raiz);

int maior(int valor1, int valor2);

void atualizarAltura(NoAVL *raiz);

int fatorBalanceamento(NoAVL *raiz);

void balancear(NoAVL **raiz);

NoAVL *rotacaoDireita(NoAVL *raiz);

NoAVL *rotacaoEsquerda(NoAVL *raiz);

void liberarAVL(NoAVL **raiz);

//funções do experimento

void gerarCodigos(int codigos[]);

void inserirCodigos(NoAVL **raiz, int codigos[]);

void realizarBuscas(NoAVL *raiz, int codigosBusca[]);

void gerarOrdemMeioAleatoria(int origem[], int destino[]);

void inverterCodigos(int codigos[]);

void embaralharCodigos(int codigos[]);

void buscarCodigoNaoCadastrado(NoAVL *raiz, int codigo);

void rodarExperimentoProdutos(void);

#endif
