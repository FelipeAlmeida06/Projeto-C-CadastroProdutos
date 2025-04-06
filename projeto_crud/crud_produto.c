#include <stdio.h>              //biblioteca
#include <stdlib.h>
#include <string.h>         

#define MAX_PRODUTOS 10     // constante com valor 10

typedef struct {
    int idProduto;
    char nomeProduto[50];
    float precoProduto;
    char categoriaProduto[30];
    int quantidadeProduto;
} Produto;

Produto produtos[MAX_PRODUTOS];
int totalProdutos = 0;

// Método para criar produtos
void criarProduto() {
    if (totalProdutos < MAX_PRODUTOS) {
        Produto novoProduto;
        novoProduto.idProduto = totalProdutos + 1;

        getchar();
        printf("Digite o nome do produto: ");
        scanf(" %49[^\n]", novoProduto.nomeProduto);

        printf("Digite o preco do produto: ");
        scanf("%f", &novoProduto.precoProduto);
        if (novoProduto.precoProduto < 0) {
            printf("Erro: Preco nao pode ser negativo. Encerrando programa.\n");
            exit(1);
        }

        getchar();
        printf("Digite a categoria do produto: ");
        scanf(" %29[^\n]", novoProduto.categoriaProduto);

        printf("Digite a quantidade em estoque: ");
        scanf("%d", &novoProduto.quantidadeProduto);
        if (novoProduto.quantidadeProduto < 0) {
            printf("Erro: Quantidade nao pode ser negativa. Encerrando programa.\n");
            exit(1);
        }

        produtos[totalProdutos] = novoProduto;
        totalProdutos++;
        printf("Produto criado com sucesso!\n");
    } else {
        printf("Erro: Limite de produtos a cadastrar atingidos.\n");
    }
}

// Método para buscar um produto na lista de produtos
Produto* buscarProduto(int id) {
    for (int i = 0; i < totalProdutos; i++) {
        if (produtos[i].idProduto == id) {
            return &produtos[i];
        }
    }
    return NULL;
}

// Método para atualizar produtos
void atualizarProduto() {
    int id;
    printf("Digite o ID do produto a ser atualizado: ");
    scanf("%d", &id);

    Produto* prod = buscarProduto(id);
    if (prod) {
        printf("Digite o novo nome do produto: ");
        getchar();
        scanf(" %49[^\n]", prod->nomeProduto);

        printf("Digite o novo preco do produto: ");
        scanf("%f", &prod->precoProduto);
        if (prod->precoProduto < 0) {
            printf("Erro: Preco nao pode ser negativo. Encerrando programa.\n");
            exit(1);
        }

        getchar();
        printf("Digite a nova categoria do produto: ");
        scanf(" %29[^\n]", prod->categoriaProduto);

        printf("Digite a nova quantidade em estoque: ");
        scanf("%d", &prod->quantidadeProduto);
        if (prod->quantidadeProduto < 0) {
            printf("Erro: Quantidade nao pode ser negativa. Encerrando programa.\n");
            exit(1);
        }

        printf("Produto atualizado com sucesso!\n");
    } else {
        printf("Produto não encontrado.\n");
    }
}

/* Não utilizado para essa primeira versão de programa
// Método para remover produtos no estoque
void removerQuantidadeDeProdutosNoEstoque() {
    int id, quantidade;
    printf("Digite o ID do produto a ser atualizado no estoque: ");
    scanf("%d", &id);

    Produto* prod = buscarProduto(id);
    if (prod) {
        printf("Quantidade atual no estoque: %d\n", prod->quantidadeProduto);
        printf("Digite a quantidade a ser removida do estoque: ");
        getchar();
        scanf("%d", &quantidade);

        if (quantidade > prod->quantidadeProduto) {
            printf("Erro: Quantidade insuficiente no estoque.\n");
        } else {
            prod->quantidadeProduto -= quantidade;
            printf("Quantidade atualizada com sucesso! Novo estoque: %d\n", prod->quantidadeProduto);
        }
    } else {
        printf("Produto não encontrado.\n");
    }
}
*/

// Método para deletar produtos
void deletarProdutos() {
    int id;
    printf("Digite o ID do produto a ser deletado: ");
    getchar();
    scanf("%d", &id);
    
    for (int i = 0; i < totalProdutos; i++) {
        if (produtos[i].idProduto == id) {
            for (int j = i; j < totalProdutos - 1; j++) {
                produtos[j] = produtos[j + 1];
            }
            totalProdutos--;
            printf("Produto deletado com sucesso!\n");
            return;
        }
    }
    printf("Produto nao encontrado.\n");
}

// Método para listar produtos
void listarProdutos() {
    printf("Lista de Produtos:\n");
    for (int i = 0; i < totalProdutos; i++) {
        printf("ID: %d | Nome: %s | Preco: R$ %.2f | Categoria: %s | Quantidade: %d\n",
               produtos[i].idProduto,
               produtos[i].nomeProduto,
               produtos[i].precoProduto,
               produtos[i].categoriaProduto,
               produtos[i].quantidadeProduto);
        printf("==============================\n");
    }
}

// Função principal do programa
int main() {
    int opcaoDesejada;
    do {
        printf("=============================================================\n");
        printf("Menu:\n");
        printf("1. Criar Produto\n");
        printf("2. Listar Produtos\n");
        printf("3. Atualizar Produto\n");
        printf("4. Deletar Produto\n");
        printf("5. Sair\n");
        printf("==============================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcaoDesejada);

        switch (opcaoDesejada)
        {
        case 1:
            criarProduto();
            break;
        case 2:
            listarProdutos();
            break;
        case 3:
            atualizarProduto();
            break;
        case 4:
            deletarProdutos();
            break;
        case 5:
            printf("Saindo do programa...\n");
            break;
        default:
            printf("Opcao invalida!\n");
        }
    } while (opcaoDesejada != 6);

    return 0;
}