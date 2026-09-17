#include"estrutura_AVL.h"

void mostrarProduto(NoAVL *raiz, int codigoProduto){
    NoAVL *noProduto;
    noProduto = buscarProduto(raiz, codigoProduto);

    if (noProduto == NULL)
        printf("\nProduto nao encontrado.\n");
        return;

    printf("\n==== Dados do Produto ===\n");
    printf("Codigo: %d\n", noProduto->produto.codigo);
    printf("Nome: %s\n", noProduto->produto.nome);

    if (noProduto->produto.fornecedor != NULL)
    {
        printf("Fornecedor: %s\n", noProduto->produto.fornecedor->nome);
        printf("Telefone: %s\n", noProduto->produto.fornecedor->telefone);
    }else{
        printf("Fornecedor: nao informado\n");
    }
    
    if (noProduto->produto.estoque != NULL)
        printf("Quantidade em estoque: %d\n", noProduto->produto.estoque->quantidade);
    else
        printf("Quantidade em estoque: nao cadastrada\n");
    
    printf("------------------------------\n");
}

NoAVL *criarNoAVL(Produto produto){
    NoAVL *novo;
    novo = (NoAVL *) malloc(sizeof(NoAVL));

    if (novo != NULL)
    {
        novo->produto= produto;
        novo->altura = 1;
        novo->esq = NULL;
        novo->dir = NULL;
    }else{
        printf("Erro ao alocar memoria.\n");
    }
    return novo;
}

void inserirAVL(NoAVL **raiz, NoAVL *novo){
    if (*raiz == NULL)
    {
        *raiz = novo;
    }else{
        if (novo->produto.codigo < (*raiz)->produto.codigo)
        {
            inserirAVL(&((*raiz)->esq), novo);
        }else if (novo->produto.codigo > (*raiz)->produto.codigo)
        {
            inserirAVL(&((*raiz)->dir), novo);
        }else{
            printf("Codigo de produto duplicado.\n");
            free(novo);
        }

        if (*raiz != NULL)
        {
            atualizarAltura(*raiz);
            balancear(raiz);
        }
    }
}

int altura(NoAVL *raiz){
    int result;

    if (raiz == NULL)
        result = 0;
    else
        result = raiz->altura;
    
    return result;
}

int maior(int valor1, int valor2){
    int result;

    if (valor1 > valor2)
        result = valor1;
    else
        result = valor2;
    
    return result;  
}

void atualizarAltura(NoAVL *raiz){
    int alturaesq;
    int alturadir;

    if (raiz != NULL)
    {
        alturaesq = altura(raiz->esq);
        alturaesq = altura(raiz->dir);

        raiz->altura = 1 + maior(alturaesq, alturadir);
    }
    
}

int fatorBalanceamento(NoAVL *raiz){
    int fator = 0;
    if (raiz != NULL)
        fator = altura(raiz->esq) - altura(raiz->dir);
    return fator;
}

void balancear(NoAVL **raiz){
    int fator;

    if (*raiz != NULL)
    {
        fatorBalanceamento(*raiz);

        if (fator == 2 && fatorBalanceamento((*raiz)->esq) >= 0)
        {
            *raiz = rotacaoDireita(*raiz);
        }
    }else if (fator == -2 && fatorBalanceamento((*raiz)->dir) <= 0)
    {
        *raiz = rotacaoesquerda(*raiz);
    }else if (fator == 2 && fatorBalanceamento((*raiz)->esq) < 0)
    {
        (*raiz)->esq = rotacaoesquerda((*raiz)->esq);
        *raiz = rotacaoDireita(*raiz);
    }else if (fator == -2 && fatorBalanceamento((*raiz)->dir) > 0)
    {
        (*raiz)->dir = rotacaoDireita((*raiz)->dir);
        *raiz = rotacaoesquerda(*raiz);
    } 
}