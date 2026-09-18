#include "estrutura_AVL.h"

void exibirMenu(void);
void limparBuffer(void);
void cadastrarProdutoManual(NoAVL **raizProdutos);
void buscarProdutoMenu(NoAVL *raizProdutos);
void cadastrarEstoqueMenu(NoAVL *raizProdutos);
void cadastrarFornecedorMenu(NoAVL *raizProdutos);

int main(void){

    NoAVL *raizProdutos = NULL;
    int opcao;

    srand((unsigned int)time(NULL));

    do
    {
        exibirMenu();

        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao)
        {
        case 1:
            cadastrarProdutoManual(&raizProdutos);
            break;

        case 2:
            printf("\nDigite o codigo do produto a buscar: ");
            buscarProdutoMenu(raizProdutos);
            break;

        case 3:
            cadastrarEstoqueMenu(raizProdutos);
            break;

        case 4:
            cadastrarFornecedorMenu(raizProdutos);
            break;

        case 5:
            rodarExperimentoProdutos();
            break;

        case 6:
            liberarAVL(&raizProdutos);
            printf("\nA arvore de produtos foi liberada da memoria.\n");
            break;

        case 0:
            printf("\nEncerrando o programa...\n");
            break;

        default:
            printf("\nOpcao invalida!\n");
            break;
        }

    } while (opcao != 0);

    liberarAVL(&raizProdutos);

    return 0;
}


void exibirMenu(void){

    printf(
        "\n"
        "              ARVORE AVL DE PRODUTOS - MENU           \n"
        "---------------------------------------------------  \n"
        "|   1  - Cadastrar produto                           |\n"
        "|   2  - Buscar produto (codigo)                     |\n"
        " ---------------------------------------------------  \n"
        "|   3  - Cadastrar estoque de um produto             |\n"
        "|   4  - Cadastrar fornecedor de um produto          |\n"
        " ---------------------------------------------------  \n"
        "| (e) Experimento com 100 codigos de produto         |\n"
        "|   5  - Rodar experimento (4 ordens x busca)        |\n"
        " ---------------------------------------------------  \n"
        "| Utilitario                                         |\n"
        "|   6  - Liberar a arvore (memoria)                  |\n"
        "|   0  - Sair                                        |\n"
        " ---------------------------------------------------  \n"
        "Escolha uma opcao: "
    );
}


void limparBuffer(void){

    int a;

    while ((a = getchar()) != '\n' && a != EOF);
}


void cadastrarProdutoManual(NoAVL **raizProdutos){
    Produto produto;
    NoAVL *novo;
    int totalAntes;
    int totalDepois;

    printf("\n    Cadastro de produto    \n");

    printf("Codigo: ");
    scanf("%d", &produto.codigo);
    limparBuffer();

    printf("Nome: ");
    fgets(produto.nome, sizeof(produto.nome), stdin);
    produto.nome[strcspn(produto.nome, "\n")] = '\0';

    produto.fornecedor = NULL;
    produto.estoque = NULL;

    totalAntes = (buscarProduto(*raizProdutos, produto.codigo) != NULL);

    novo = criarNoAVL(produto);
    inserirAVL(raizProdutos, novo);

    totalDepois = (buscarProduto(*raizProdutos, produto.codigo) != NULL);

    if (!totalAntes && totalDepois)
        printf("\nProduto cadastrado com sucesso!\n");
    else if (totalAntes)
        printf("\nJa existe um produto com esse codigo.\n");
}


void buscarProdutoMenu(NoAVL *raizProdutos){
    int codigo;
    int passos;
    NoAVL *resultado;

    scanf("%d", &codigo);
    limparBuffer();

    resultado = buscarProduto(raizProdutos, codigo);

    if (resultado != NULL)
    {
        mostrarProduto(raizProdutos, codigo);

        buscarComPassos(raizProdutos, codigo, &passos);

        printf("Numero de passos ate encontrar: %d\n", passos);
    }
    else
    {
        printf("\nProduto nao encontrado.\n");
    }
}


void cadastrarEstoqueMenu(NoAVL *raizProdutos){
    int codigo;
    int quantidade;

    printf("\nDigite o codigo do produto: ");
    scanf("%d", &codigo);

    printf("Digite a quantidade em estoque: ");
    scanf("%d", &quantidade);
    limparBuffer();

    if (cadastrarEstoque(raizProdutos, codigo, quantidade))
        printf("\nEstoque cadastrado com sucesso!\n");
    else
        printf("\nProduto nao encontrado.\n");
}

void cadastrarFornecedorMenu(NoAVL *raizProdutos)
{
    int codigoProduto;
    int codigoFornecedor;
    char nome[100];
    char telefone[30];

    printf("\n========== Cadastro de Fornecedor ==========\n");

    printf("Digite o codigo do produto: ");
    scanf("%d", &codigoProduto);
    limparBuffer();

    
    if (buscarProduto(raizProdutos, codigoProduto) == NULL)
    {
        printf("\nProduto nao encontrado.\n");
        return;
    }

    printf("Codigo do fornecedor: ");
    scanf("%d", &codigoFornecedor);
    limparBuffer();

    printf("Nome do fornecedor: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    printf("Telefone do fornecedor: ");
    fgets(telefone, sizeof(telefone), stdin);
    telefone[strcspn(telefone, "\n")] = '\0';

    if (cadastrarFornecedor(raizProdutos,codigoProduto,codigoFornecedor,nome,telefone))
        printf("\nFornecedor cadastrado com sucesso!\n");

    else
        printf("\nNao foi possivel cadastrar o fornecedor.\n");
    
}