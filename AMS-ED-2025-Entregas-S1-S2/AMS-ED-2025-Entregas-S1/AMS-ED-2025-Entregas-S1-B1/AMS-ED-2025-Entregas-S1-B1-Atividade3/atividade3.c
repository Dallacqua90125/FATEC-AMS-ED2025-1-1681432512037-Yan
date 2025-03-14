#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pedido {
    int numero;
    char cliente[50];
    char descricao[100];
    int quantidade;
    char status[20];
    struct Pedido *proximo;
} Pedido;

Pedido* criarLista() {
    return NULL;
}

Pedido* inserirPedido(Pedido *head, int numero, char *cliente, char *descricao, int quantidade, char *status) {
    Pedido *novo = (Pedido*) malloc(sizeof(Pedido));

    if (novo == NULL) {
        printf("Erro ao alocar memória!\n");
        return head;
    }

    novo->numero = numero;
    strcpy(novo->cliente, cliente);
    strcpy(novo->descricao, descricao);
    novo->quantidade = quantidade;
    strcpy(novo->status, status);
    novo->proximo = head;

    return novo;
}

void obterPedido(Pedido *head, int numero) {
    Pedido *atual = head;

    while (atual != NULL) {
        if (atual->numero == numero) {
            printf("Pedido #%d\n", atual->numero);
            printf("Cliente: %s\n", atual->cliente);
            printf("Descrição: %s\n", atual->descricao);
            printf("Quantidade: %d\n", atual->quantidade);
            printf("Status: %s\n", atual->status);
            return;
        }
        atual = atual->proximo;
    }
    printf("Pedido não encontrado!\n");
}

void atualizarStatus(Pedido *head, int numero, char *novo_status) {
    Pedido *atual = head;

    while (atual != NULL) {
        if (atual->numero == numero) {
            strcpy(atual->status, novo_status);
            printf("Status do pedido #%d atualizado para: %s\n", numero, novo_status);
            return;
        }
        atual = atual->proximo;
    }
    printf("Pedido não encontrado!\n");
}

Pedido* deletarPedido(Pedido *head, int numero) {
    Pedido *atual = head, *anterior = NULL;

    while (atual != NULL && atual->numero != numero) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Pedido não encontrado!\n");
        return head;
    }

    if (anterior == NULL) {
        head = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual);
    printf("Pedido #%d removido com sucesso!\n", numero);
    return head;
}

void liberarLista(Pedido *head) {
    Pedido *atual = head;
    
    while (atual != NULL) {
        Pedido *temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    
    printf("Memória liberada!\n");
}

int main() {
    Pedido *lista = criarLista();
    int opcao, numero, quantidade;
    char cliente[50], descricao[100], status[20];

    do {
        printf("\nGerenciamento de Pedidos do Restaurante\n");
        printf("1. Inserir pedido\n");
        printf("2. Obter pedido\n");
        printf("3. Atualizar status\n");
        printf("4. Deletar pedido\n");
        printf("5. Liberar lista e sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Número do pedido: ");
                scanf("%d", &numero);
                printf("Nome do cliente: ");
                scanf(" %[^\n]", cliente);
                printf("Descrição do prato: ");
                scanf(" %[^\n]", descricao);
                printf("Quantidade: ");
                scanf("%d", &quantidade);
                printf("Status inicial: ");
                scanf(" %[^\n]", status);
                lista = inserirPedido(lista, numero, cliente, descricao, quantidade, status);
                break;

            case 2:
                printf("Digite o número do pedido: ");
                scanf("%d", &numero);
                obterPedido(lista, numero);
                break;

            case 3:
                printf("Digite o número do pedido: ");
                scanf("%d", &numero);
                printf("Novo status: ");
                scanf(" %[^\n]", status);
                atualizarStatus(lista, numero, status);
                break;

            case 4:
                printf("Digite o número do pedido a ser removido: ");
                scanf("%d", &numero);
                lista = deletarPedido(lista, numero);
                break;

            case 5:
                liberarLista(lista);
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 5);

    return 0;
}
