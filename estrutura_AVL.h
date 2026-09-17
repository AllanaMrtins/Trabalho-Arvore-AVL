#ifndef ARVORE_BINARIA_BUSCA
#define ARVORE_BINARIA_BUSCA
#include<stdio.h>
#include<stdlib.h>

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

int cadastrarEstoque(NoAVL *raiz, int codigoProduto, int quantidade);

void mostarProduto(NoAVL *raiz, int codigoProduto);

NoAVL *criarNoAVL(Produto produto);

void inserirAVL(NoAVL **raiz, NoAVL *novo);

int altura(NoAVL *raiz);

int maior(int valor1, int valor2);

void atualizarAltura(NoAVL *raiz);

int fatorBalanceamento(NoAVL *raiz);

void balancear(NoAVL **raiz);



#endif