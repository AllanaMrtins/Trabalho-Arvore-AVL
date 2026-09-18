#include "estrutura_AVL.h"

NoAVL *buscarProduto(NoAVL *raiz, int codigoProduto){
    NoAVL *resultado;

    if (raiz == NULL)
        resultado = NULL;

    else if (codigoProduto == raiz->produto.codigo)
        resultado = raiz;

    else if (codigoProduto < raiz->produto.codigo)
        resultado = buscarProduto(raiz->esq, codigoProduto);

    else
        resultado = buscarProduto(raiz->dir, codigoProduto);

    return resultado;
}

int buscarComPassos(NoAVL *raiz, int codigoProduto, int *passos){
    int encontrado = 0;
    *passos = 0;

    while (raiz != NULL && encontrado == 0)
    {
        (*passos)++;

        if (codigoProduto == raiz->produto.codigo)
            encontrado = 1;

        else if (codigoProduto < raiz->produto.codigo)
            raiz = raiz->esq;
        else
            raiz = raiz->dir;
    }
    return encontrado;
}

Estoque *criarEstoque(int codigoProduto, int quantidade)
{
    Estoque *novo;
    novo = (Estoque *)malloc(sizeof(Estoque));
    if (novo != NULL)
    {
        novo->codigoProduto = codigoProduto;
        novo->quantidade = quantidade;
    }
    return novo;
}

Fornecedor *criarFornecedor(int codigo, char nome[], char telefone[])
{
    Fornecedor *novo;

    novo = (Fornecedor *)malloc(sizeof(Fornecedor));

    if (novo != NULL)
    {
        novo->codigo = codigo;

        strcpy(novo->nome, nome);
        strcpy(novo->telefone, telefone);
    }

    return novo;
}

int cadastrarEstoque(NoAVL *raiz, int codigoProduto, int quantidade)
{
    if (raiz == NULL)
        return 0;

    if (codigoProduto == raiz->produto.codigo)
    {
        if (raiz->produto.estoque == NULL)
            raiz->produto.estoque = criarEstoque(codigoProduto, quantidade);
        else
            raiz->produto.estoque->quantidade = quantidade;

        return 1;
    }

    if (codigoProduto < raiz->produto.codigo)
        return cadastrarEstoque(raiz->esq, codigoProduto, quantidade);

    return cadastrarEstoque(raiz->dir, codigoProduto, quantidade);
}

int cadastrarFornecedor(NoAVL *raiz, int codigoProduto, int codigoFornecedor, char nome[], char telefone[])
{
    int resultado = 0;
    Fornecedor *novo;

    if (raiz != NULL)
    {
        if (codigoProduto == raiz->produto.codigo)
        {
            if (raiz->produto.fornecedor == NULL)
            {
                novo = criarFornecedor(codigoFornecedor, nome, telefone);

                if (novo != NULL)
                {
                    raiz->produto.fornecedor = novo;
                    resultado = 1;
                }
            }
            else
            {
                raiz->produto.fornecedor->codigo = codigoFornecedor;
                strcpy(raiz->produto.fornecedor->nome, nome);
                strcpy(raiz->produto.fornecedor->telefone, telefone);

                resultado = 1;
            }
        }
        else if (codigoProduto < raiz->produto.codigo)
        
            resultado = cadastrarFornecedor(raiz->esq, codigoProduto,codigoFornecedor, nome, telefone);
        
        else
        
            resultado = cadastrarFornecedor(raiz->dir, codigoProduto,codigoFornecedor, nome, telefone);
    }

    return resultado;
}

void mostrarProduto(NoAVL *raiz, int codigoProduto){
    NoAVL *noProduto;
    noProduto = buscarProduto(raiz, codigoProduto);

    if (noProduto == NULL)
    {
        printf("\nProduto nao encontrado.\n");
        return;
    }

    printf("\n==== Dados do Produto ===\n");
    printf("Codigo: %d\n", noProduto->produto.codigo);
    printf("Nome: %s\n", noProduto->produto.nome);

    if (noProduto->produto.fornecedor != NULL)
    {
        printf("Fornecedor: %s\n", noProduto->produto.fornecedor->nome);
        printf("Telefone: %s\n", noProduto->produto.fornecedor->telefone);
    }
    else
    {
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
        novo->produto = produto;
        novo->altura = 1;
        novo->esq = NULL;
        novo->dir = NULL;
    }
    else
    {
        printf("Erro ao alocar memoria.\n");
    }
    return novo;
}

void inserirAVL(NoAVL **raiz, NoAVL *novo){
    if (*raiz == NULL)
    {
        *raiz = novo;
    }
    else
    {
        if (novo->produto.codigo < (*raiz)->produto.codigo)
        {
            inserirAVL(&((*raiz)->esq), novo);
        }
        else if (novo->produto.codigo > (*raiz)->produto.codigo)
        {
            inserirAVL(&((*raiz)->dir), novo);
        }
        else
        {
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
        alturadir = altura(raiz->dir);

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
        fator = fatorBalanceamento(*raiz);

        if (fator == 2 && fatorBalanceamento((*raiz)->esq) >= 0)
        {
            *raiz = rotacaoDireita(*raiz);
        }
        else if (fator == -2 && fatorBalanceamento((*raiz)->dir) <= 0)
        {
            *raiz = rotacaoEsquerda(*raiz);
        }
        else if (fator == 2 && fatorBalanceamento((*raiz)->esq) < 0)
        {
            (*raiz)->esq = rotacaoEsquerda((*raiz)->esq);
            *raiz = rotacaoDireita(*raiz);
        }
        else if (fator == -2 && fatorBalanceamento((*raiz)->dir) > 0)
        {
            (*raiz)->dir = rotacaoDireita((*raiz)->dir);
            *raiz = rotacaoEsquerda(*raiz);
        }
    }
}

NoAVL *rotacaoDireita(NoAVL *raiz){
    NoAVL *novaRaiz;
    NoAVL *subarvore;

    novaRaiz = NULL;
    subarvore = NULL;

    if (raiz != NULL && raiz->esq != NULL)
    {
        novaRaiz = raiz->esq;
        subarvore = novaRaiz->dir;

        novaRaiz->dir = raiz;
        raiz->esq = subarvore;

        atualizarAltura(raiz);
        atualizarAltura(novaRaiz);
    }
    else
    {
        novaRaiz = raiz;
    }
    return novaRaiz;
}

NoAVL *rotacaoEsquerda(NoAVL *raiz){
    NoAVL *novaRaiz;
    NoAVL *subarvore;

    novaRaiz = NULL;
    subarvore = NULL;

    if (raiz != NULL && raiz->dir != NULL)
    {
        novaRaiz = raiz->dir;
        subarvore = novaRaiz->esq;

        novaRaiz->esq = raiz;
        raiz->dir = subarvore;

        atualizarAltura(raiz);
        atualizarAltura(novaRaiz);
    }
    else
    {
        novaRaiz = raiz;
    }
    return novaRaiz;
}

void liberarAVL(NoAVL **raiz){
    if (*raiz != NULL)
    {
        liberarAVL(&(*raiz)->esq);
        liberarAVL(&(*raiz)->dir);

        if ((*raiz)->produto.fornecedor != NULL)
            free((*raiz)->produto.fornecedor);

        if ((*raiz)->produto.estoque != NULL)
            free((*raiz)->produto.estoque);

        free(*raiz);
        *raiz = NULL;
    }
}

// funcoes experimento

void gerarCodigos(int codigos[]){
    for (int i = 0; i < 100; i++)
    {
        codigos[i] = 100 + i;
    }
}

void inserirCodigos(NoAVL **raiz, int codigos[]){
    Produto produto;
    NoAVL *novo;

    for (int i = 0; i < 100; i++)
    {
        produto.codigo = codigos[i];
        sprintf(produto.nome, "Produto %04d", codigos[i]);
        produto.fornecedor = NULL;
        produto.estoque = NULL;

        novo = criarNoAVL(produto);
        inserirAVL(raiz, novo);
    }
}

void realizarBuscas(NoAVL *raiz, int codigosBusca[]){
    int passos;
    for (int i = 0; i < 10; i++)
    {
        buscarComPassos(raiz, codigosBusca[i], &passos);
        printf("Codigo %04d -> %d passos\n", codigosBusca[i], passos);
    }
}

void gerarOrdemMeioAleatoria(int origem[], int destino[]){
    int usados[100];
    int pos, aux, j;

    for (int i = 0; i < 100; i++)
    {
        usados[i] = 0;
    }
    destino[0] = origem[50];
    usados[50] = 1;

    for (int i = 1; i < 100; i++)
    {
        do
        {
            pos = rand() % 100;
        } while (usados[pos] == 1);

        destino[i] = origem[pos];
        usados[pos] = 1;
    }

    for (int i = 99; i > 1; i--)
    {
        j = 1 + rand() % i;
        aux = destino[i];
        destino[i] = destino[j];
        destino[j] = aux;
    }
}

void inverterCodigos(int codigos[]){
    int aux;
    for (int i = 0; i < 50; i++)
    {
        aux = codigos[i];
        codigos[i] = codigos[99 - i];
        codigos[99 - i] = aux;
    }
}

void embaralharCodigos(int codigos[]){
    int i, j, aux;

    for (i = 99; i > 0; i--){
        j = rand() % (i + 1);

        aux = codigos[i];
        codigos[i] = codigos[j];
        codigos[j] = aux;
    }
}

void buscarCodigoNaoCadastrado(NoAVL *raiz, int codigo){
    int passos, encontrado;

    encontrado = buscarComPassos(raiz, codigo, &passos);

    if (encontrado == 0)
        printf("Codigo nao cadastrado: %04d -> %d passos\n", codigo, passos);
    else
        printf("Codigo encontrado: %04d -> %d passos\n", codigo, passos);
}

void rodarExperimentoProdutos(void){

    int codigos[100];
    int codigosCrescente[100];
    int codigosDecrescente[100];
    int codigosMeioAleatorio[100];
    int codigosAleatorio[100];
    int codigosBusca[10];

    int i;
    int codigoNaoCadastrado = 9999;
    NoAVL *raiz = NULL;

    gerarCodigos(codigos);

    for (i = 0; i < 10; i++)
        codigosBusca[i] = codigos[i];


    for (i = 0; i < 100; i++)
        codigosCrescente[i] = codigos[i];

    printf("\n    Experimento 1 - Ordem crescente    \n");
    inserirCodigos(&raiz, codigosCrescente);
    realizarBuscas(raiz, codigosBusca);

    printf("\nBusca por codigo nao cadastrado:\n");
    buscarCodigoNaoCadastrado(raiz, codigoNaoCadastrado);

    printf("Altura final da AVL: %d\n", altura(raiz));

    liberarAVL(&raiz);


    for (i = 0; i < 100; i++)
        codigosDecrescente[i] = codigos[i];
    inverterCodigos(codigosDecrescente);

    printf("\n    Experimento 2 - Ordem decrescente    \n");
    inserirCodigos(&raiz, codigosDecrescente);
    realizarBuscas(raiz, codigosBusca);

    printf("\nBusca por codigo nao cadastrado:\n");
    buscarCodigoNaoCadastrado(raiz, codigoNaoCadastrado);

    printf("Altura final da AVL: %d\n", altura(raiz));

    liberarAVL(&raiz);


    gerarOrdemMeioAleatoria(codigos, codigosMeioAleatorio);

    printf("\n   Experimento 3 - Codigo do meio primeiro + aleatorio    \n");
    inserirCodigos(&raiz, codigosMeioAleatorio);
    realizarBuscas(raiz, codigosBusca);

    printf("\nBusca por codigo nao cadastrado:\n");
    buscarCodigoNaoCadastrado(raiz, codigoNaoCadastrado);

    printf("Altura final da AVL: %d\n", altura(raiz));

    liberarAVL(&raiz);


    for (i = 0; i < 100; i++)
        codigosAleatorio[i] = codigos[i];
    embaralharCodigos(codigosAleatorio);

    printf("\n    Experimento 4 - Totalmente aleatorio    \n");
    inserirCodigos(&raiz, codigosAleatorio);
    realizarBuscas(raiz, codigosBusca);

    printf("\nBusca por codigo nao cadastrado:\n");
    buscarCodigoNaoCadastrado(raiz, codigoNaoCadastrado);

    printf("Altura final da AVL: %d\n", altura(raiz));

    liberarAVL(&raiz);

    printf("\n--- FIM DO EXPERIMENTO ---\n");
}
