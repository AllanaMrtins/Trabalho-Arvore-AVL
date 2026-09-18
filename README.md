# Árvore AVL de Produtos — Sistema de Supermercado

Projeto em linguagem C que implementa uma Árvore AVL para gerenciar produtos, fornecedores e
estoque de um supermercado, utilizando o paradigma estruturado (structs e funções, sem
orientação a objetos).

## Descrição do Projeto

O sistema permite cadastrar produtos, consultar informações (nome, fornecedor e estoque) por
código, cadastrar a quantidade em estoque e o fornecedor de um produto já existente, e
executar um experimento com 100 códigos de produto para analisar o desempenho da árvore sob
diferentes ordens de inserção.

## Estrutura de Arquivos

```
.
├── estrutura_AVL.h   # Definições de structs e protótipos de funções
├── funcoes.c         # Implementação das funções da árvore AVL
└── main.c            # Menu interativo do programa
```

## Estruturas de Dados

```c
typedef struct Fornecedor {
    int codigo;
    char nome[100];
    char telefone[20];
} Fornecedor;

typedef struct Estoque {
    int codigoProduto;
    int quantidade;
} Estoque;

typedef struct Produto {
    int codigo;
    char nome[100];
    Fornecedor *fornecedor;
    Estoque *estoque;
} Produto;

typedef struct NoAVL {
    Produto produto;
    int altura;
    struct NoAVL *esq;
    struct NoAVL *dir;
} NoAVL;
```

Cada nó da árvore (`NoAVL`) armazena um `Produto`. O produto referencia, por ponteiro, seu
`Fornecedor` e seu `Estoque`, permitindo que essas informações sejam associadas ou atualizadas
de forma independente, sem duplicar dados dentro da estrutura do produto.

## Compilação

```bash
gcc main.c funcoes.c -o programa
```

## Execução

```bash
./programa
```

## Menu do Programa

```
              ARVORE AVL DE PRODUTOS - MENU
---------------------------------------------------
|   1  - Cadastrar produto                         |
|   2  - Buscar produto (codigo)                   |
---------------------------------------------------
|   3  - Cadastrar estoque de um produto           |
|   4  - Cadastrar fornecedor de um produto        |
---------------------------------------------------
| (e) Experimento com 100 codigos de produto       |
|   5  - Rodar experimento (4 ordens x busca)      |
---------------------------------------------------
| Utilitario                                       |
|   6  - Liberar a arvore (memoria)                |
|   0  - Sair                                      |
---------------------------------------------------
```

## Funcionalidades por Item do Trabalho

### (a) Estruturas de dados
`Fornecedor`, `Estoque`, `Produto` e `NoAVL`, conforme mostrado acima. O produto se liga ao
fornecedor e ao estoque por ponteiro, e cada nó da árvore guarda um produto completo.

### (b) Fluxograma de cadastro de estoque
Descrito no relatório do trabalho (não faz parte do código-fonte).

### (c) Cadastro de estoque na árvore AVL
Função `cadastrarEstoque`, acessível pela opção **3** do menu. Localiza o produto pelo código
e cria ou atualiza o registro de estoque associado a ele.

```c
int cadastrarEstoque(NoAVL *raiz, int codigoProduto, int quantidade);
```

### Cadastro de fornecedor de um produto
Acessível pela opção **4** do menu. Localiza o produto pelo código e cria ou atualiza o
registro de fornecedor associado a ele, permitindo que a função do item (d) exiba essa
informação junto com os demais dados do produto.

### (d) Exibição de dados de um produto
Função `mostrarProduto`, acessível pela opção **2** do menu. Recebe o código do produto e
exibe nome, fornecedor (se cadastrado) e quantidade em estoque (se cadastrada).

```c
void mostrarProduto(NoAVL *raiz, int codigoProduto);
```

### (e) Experimento com 100 códigos de produto
Função `rodarExperimentoProdutos`, acessível pela opção **5** do menu. Gera 100 códigos e os
insere na árvore AVL em quatro ordens distintas, medindo a quantidade de passos (nós
percorridos) necessária para localizar 10 códigos fixos e um código não cadastrado em cada
cenário:

1. **Ordem crescente** — códigos inseridos na ordem em que foram gerados.
2. **Ordem decrescente** — vetor invertido antes da inserção (`inverterCodigos`).
3. **Código do meio primeiro + aleatório** — o código central do vetor é inserido primeiro,
   e os demais em ordem aleatória (`gerarOrdemMeioAleatoria`).
4. **Totalmente aleatório** — todos os 100 códigos embaralhados antes da inserção
   (`embaralharCodigos`).

Ao final de cada cenário, o programa imprime a altura final da árvore, permitindo observar
o efeito do balanceamento AVL sobre cada ordem de inserção.

## Balanceamento AVL

Diferentemente de uma árvore binária de busca simples, a AVL mantém automaticamente o
equilíbrio entre suas subárvores após cada inserção, por meio do fator de balanceamento e das
rotações simples e duplas:

- `atualizarAltura` — recalcula a altura de um nó após inserção
- `fatorBalanceamento` — calcula a diferença de altura entre as subárvores esquerda e direita
- `balancear` — aplica rotação simples (`rotacaoDireita` / `rotacaoEsquerda`) ou dupla quando
  o fator de balanceamento de um nó atinge 2 ou -2

Isso garante que, mesmo em ordens de inserção desfavoráveis (crescente ou decrescente), a
árvore permaneça com altura próxima de log₂(n), ao contrário de uma ABB comum, que se
degenera para uma lista nesses casos.

## Observações

- Os 10 códigos buscados em `realizarBuscas` são sempre os 10 primeiros valores gerados por
  `gerarCodigos`, garantindo que a comparação entre os quatro cenários seja justa.
- A função `liberarAVL` percorre a árvore em pós-ordem, liberando `fornecedor` e `estoque` de
  cada produto (quando alocados) antes de liberar o próprio nó, evitando vazamento de memória.
- O projeto não implementa remoção de produtos, por não ser um requisito do enunciado.
