#include <stdio.h>              // biblioteca para entrada e saida de dados
#include <stdlib.h>             // biblioteca para gerenciamento e conversão de tipos
#include <string.h>             // biblioteca para manipulação de strings

#define MAX_PRODUTOS 10     // constante com valor 10, número máximo de produtos que podem ser cadastrados
#define MAX_CARRINHO 20     // constante com valor 20,  número máximo de itens que o carrinho de compras pode armazenar

typedef struct {        // struct -> estrutura Produto
    int idProduto;
    char nomeProduto[50];
    float precoProduto;
    char categoriaProduto[30];
    int quantidadeProduto;
} Produto;

Produto produtos[MAX_PRODUTOS];     // vetor de produtos que estão no estoque
Produto carrinho[MAX_CARRINHO];     // vetor de itens de um carrinho de compras
int totalProdutos = 0;      // contador de quantos produtos foram cadastrados
int totalCarrinho = 0;      // contador de quantos produtos estão no carrinho

// Método para criar produtos
void criarProduto() {
    if (totalProdutos < MAX_PRODUTOS) {         // verifica se ainda há espaço para cadastrar mais produtos
        Produto novoProduto;        // ceclara um novo produto
        novoProduto.idProduto = totalProdutos + 1;      // atribui um ID sequencial ao produto

        getchar();  // limpa o buffer do teclado para evitar problemas na leitura com scanf
        printf("Digite o nome do produto: ");
        scanf(" %49[^\n]", novoProduto.nomeProduto);   // 49 caracteres com espaços

        printf("Digite o preco do produto: ");
        scanf("%f", &novoProduto.precoProduto);
        if (novoProduto.precoProduto < 0) {     // verifica se o preço é válido
            printf("Erro: Preco nao pode ser negativo. Encerrando programa.\n");
            exit(1);    // encerra o programa em caso de erro
        }

        getchar();
        printf("Digite a categoria do produto: ");
        scanf(" %29[^\n]", novoProduto.categoriaProduto);   // 29 caracteres com espaços

        printf("Digite a quantidade em estoque: ");
        scanf("%d", &novoProduto.quantidadeProduto);
        if (novoProduto.quantidadeProduto < 0) {     // verifica se a quantidade é válido
            printf("Erro: Quantidade nao pode ser negativa. Encerrando programa.\n");
            exit(1);    // encerra o programa em caso de erro
        }

        produtos[totalProdutos] = novoProduto;      // adiciona o novo produto ao vetor de produtos
        totalProdutos++;      // incrementa o número total de produtos cadastrados
        printf("Produto criado com sucesso!\n");
    } else {
        printf("Erro: Limite de produtos a cadastrar atingidos.\n");        // limite de produtos foi atingido
    }
}

// Método para buscar um produto na lista de produtos
Produto* buscarProduto(int id) {
    for (int i = 0; i < totalProdutos; i++) {   // percorre todos os produtos cadastrados
        if (produtos[i].idProduto == id) {      // se encontrar o ID correspondente
            return &produtos[i];        // retorna o endereço do produto encontrado
        }
    }
    return NULL;    // produto não existe
}

// Método para atualizar produtos
void atualizarProduto() {
    int id;
    printf("Digite o ID do produto a ser atualizado: ");
    scanf("%d", &id);

    // chama a função buscarProduto(id), passando o id de um produto que se quer encontrar
    Produto* prod = buscarProduto(id);      // Produto* é um ponteiro e, é armazenado na variavel prod
    if (prod) {
        printf("Digite o novo nome do produto: ");
        getchar();
        scanf(" %49[^\n]", prod->nomeProduto);   // 49 caracteres digitados e, armazena no campo nomeProduto da struct Produto

        printf("Digite o novo preco do produto: ");
        scanf("%f", &prod->precoProduto);
        if (prod->precoProduto < 0) {
            printf("Erro: Preco nao pode ser negativo. Encerrando programa.\n");
            exit(1);
        }

        getchar();
        printf("Digite a nova categoria do produto: ");
        scanf(" %29[^\n]", prod->categoriaProduto);   // 29 caracteres digitados e, armazena no campo categoriaProduto da struct Produto

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

// Método para deletar produtos
void deletarProdutos() {
    int id;
    printf("Digite o ID do produto a ser deletado: ");
    getchar();
    scanf("%d", &id);
    
    for (int i = 0; i < totalProdutos; i++) {                   // percorre o vetor de produtos
        if (produtos[i].idProduto == id) {                      // verifica se o produto com o ID existe
            for (int j = i; j < totalProdutos - 1; j++) {       // desloca todos os produtos seguintes para a esquerda
                produtos[j] = produtos[j + 1];                  // copia o próximo produto para a posição atual
            }
            totalProdutos--;              // decrementa o total de produtos cadastrados
            printf("Produto deletado com sucesso!\n");
            return;
        }
    }
    printf("Produto nao encontrado.\n");        // se o id não for encontrado
}

// Método para listar produtos
void listarProdutos() {
    printf("Lista de Produtos:\n");
    for (int i = 0; i < totalProdutos; i++) {       // percorre o vetor de produtos
        printf("ID: %d | Nome: %s | Preco: R$ %.2f | Categoria: %s | Quantidade: %d\n",
               produtos[i].idProduto,
               produtos[i].nomeProduto,
               produtos[i].precoProduto,
               produtos[i].categoriaProduto,
               produtos[i].quantidadeProduto);
        printf("==============================\n");         // linha separadora
    }
}

// Método para criar carrinho de compras
void criarCarrinho() {
    if (totalProdutos == 0) {           // se total for igual a zero, nao existem produtos criados
        printf("Nenhum produto cadastrado. Nao e possivel criar carrinho.\n");
        return;
    }

    int idEscolhido;
    int quantidade;
    float totalCompra = 0.0;
    char continuar;

    printf("Produtos disponíveis:\n");
    listarProdutos();    // lista todos os produtos cadastrados

    do {
        printf("Digite o ID do produto que deseja adicionar ao carrinho: ");
        scanf("%d", &idEscolhido);

        Produto* prod = buscarProduto(idEscolhido);
        if (prod == NULL) {
            printf("Produto nao encontrado. Encerrando o programa.\n");
            exit(1);
        }

        printf("Digite a quantidade do produto que deseja adicionar: ");
        scanf("%d", &quantidade);
        if (quantidade <= 0) {          // se quantidade a adicionar for menor igual a zero
            printf("Quantidade invalida. Encerrando o programa.\n");
            exit(1);
        }

        if (quantidade > prod->quantidadeProduto) {     // se quantidade informada ultrapassar o estoque máximo
            printf("Erro: Quantidade solicitada excede o estoque disponível de (%d unidades.)\n", prod->quantidadeProduto);
            printf("Encerrando o programa.\n");
            exit(1);
        }

        // atualiza estoque
        prod->quantidadeProduto -= quantidade; 

        // adiciona ao carrinho
        Produto itemCarrinho = *prod;
        itemCarrinho.quantidadeProduto = quantidade;

        carrinho[totalCarrinho] = itemCarrinho;
        totalCompra += itemCarrinho.precoProduto * quantidade;
        totalCarrinho++;

        printf("Produto adicionado ao carrinho!\n");
        printf("Deseja adicionar mais um produto? (s/n): ");
        getchar();
        scanf("%c", &continuar);

    } while ((continuar == 's' || continuar == 'S') && totalCarrinho < MAX_CARRINHO);
    // loop continua enquanto: o usuário responder 's' ou 'S' à pergunta "Deseja adicionar mais um produto?"
    // e o carrinho não estiver cheio (limitado por MAX_CARRINHO).

    printf("Carrinho finalizado.\n");
    printf("Itens no carrinho:\n");
    for (int i = 0; i < totalCarrinho; i++) {
        printf("- %s | Quantidade: %d | Preco unitario: R$ %.2f | Subtotal: R$ %.2f\n",
               carrinho[i].nomeProduto,
               carrinho[i].quantidadeProduto,
               carrinho[i].precoProduto,
               carrinho[i].precoProduto * carrinho[i].quantidadeProduto);
    }

    printf("Total da compra: R$ %.2f\n", totalCompra);   // exibe o total da compra, somando os valores dos produtos adicionados ao carrinho
}

// Método para limpar o carrinho
void limparCarrinho() {
    if (totalCarrinho == 0) {
        printf("Nao existe um carrinho criado. Encerrando o programa.\n");
        exit(1);
    }

    // devolver os itens ao estoque
    for (int i = 0; i < totalCarrinho; i++) {
        Produto* prod = buscarProduto(carrinho[i].idProduto);
        if (prod != NULL) {
            prod->quantidadeProduto += carrinho[i].quantidadeProduto;
        }
    }

    totalCarrinho = 0;
    printf("Compra cancelada com sucesso! Produtos devolvidos ao estoque.\n");
}

// Método para filtrar produtos por ID
void filtrarProdutoPorId() {
    if (totalProdutos == 0) {
        printf("Nao existe produtos cadastrados. Nenhum produto para filtrar.\n");
        return;
    }

    int id;
    printf("Digite o ID do produto: ");
    scanf("%d", &id);
    Produto* prod = buscarProduto(id);
    if (prod != NULL) {
        printf("ID: %d | Nome: %s | Preco: R$ %.2f | Categoria: %s | Quantidade: %d\n",
               prod->idProduto,
               prod->nomeProduto,
               prod->precoProduto,
               prod->categoriaProduto,
               prod->quantidadeProduto);
    } else {
        printf("Produto nao encontrado.\n");
        return;
    }
}

// Método para filtrar produtos por Nome
void filtrarProdutoPorNome() {
    if (totalProdutos == 0) {
        printf("Nao existe produtos cadastrados. Encerrando o programa.\n");
        return;
    }

    char nome[50];
    getchar();
    printf("Digite o nome do produto: ");
    scanf(" %49[^\n]", nome);    // 49 caracteres

    int encontrado = 0;
    for (int i = 0; i < totalProdutos; i++) {
        // strcasecmp -> compara o nome do produto com o nome informado pelo usuário (ignorando diferenças de maiúsculas/minúsculas)
        if (strcasecmp(produtos[i].nomeProduto, nome) == 0) {
            printf("ID: %d | Nome: %s | Preco: R$ %.2f | Categoria: %s | Quantidade: %d\n",
                   produtos[i].idProduto,
                   produtos[i].nomeProduto,
                   produtos[i].precoProduto,
                   produtos[i].categoriaProduto,
                   produtos[i].quantidadeProduto);
            encontrado = 1;     // o produto foi encontrado
        }
    }

    if (!encontrado) {      // enquanto não foi encontrado
        printf("Produto nao encontrado.\n");
    }
}

// Função principal do programa
int main() {
    int opcaoDesejada;    // opcao escolhida pelo usuario
    do {
        printf("=============================================================\n");
        printf("Menu:\n");
        printf("1. Criar Produto\n");
        printf("2. Listar Produtos\n");
        printf("3. Atualizar Produto\n");
        printf("4. Deletar Produto\n");
        printf("5. Criar Carrinho de Compras\n");
        printf("6. Filtrar Produto por ID\n");
        printf("7. Filtrar Produto por Nome\n");
        printf("8. Limpar Carrinho de Compras\n");
        printf("9. Sair\n");
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
            criarCarrinho();
            break;
        case 6:
            filtrarProdutoPorId();
            break;
        case 7:
            filtrarProdutoPorNome();
            break;
        case 8:
            limparCarrinho();
            break;
        case 9:
            printf("Saindo do programa...\n");    // saindo
            break;
        default:
            printf("Opcao invalida!\n");    // opcao desconhecida escolhida pelo usuario
        }
    } while (opcaoDesejada != 9);    // enquanto opcao escolhida for diferente de 9

    return 0;
}