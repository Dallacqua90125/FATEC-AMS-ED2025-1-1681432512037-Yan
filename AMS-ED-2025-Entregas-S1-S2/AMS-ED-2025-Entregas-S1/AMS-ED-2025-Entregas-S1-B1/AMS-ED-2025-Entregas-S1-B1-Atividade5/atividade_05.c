/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: S1-B1-5                                 */
/*             Objetivo: << Transforma Lista Ligada em Pilha >>                     */
/*                                                                                  */
/*                                    Autores:  Yan Rogério Dall'Acqua Rodrigues    */
/*                                                                                  */
/*                                                                                  */
/*                                                                                  */
/*                                                                                  */
/*                                                                                  */
/*                                                                  Data:01/04/2025 */
/*----------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição de constantes
#define MAX_NOME 50
#define MAX_DESCRICAO 100
#define MAX_STATUS 20
#define NUM_STATUS 4

// Enumeração para os status possíveis
typedef enum {
    STATUS_PENDENTE = 1,
    STATUS_EM_PREPARO = 2,
    STATUS_PRONTO = 3,
    STATUS_ENTREGUE = 4
} StatusPedido;

// Estrutura para armazenar informações do pedido
typedef struct {
    int numero;
    char cliente[MAX_NOME];
    char descricao[MAX_DESCRICAO];
    int quantidade;
    StatusPedido status;
    struct Pedido* proximo;
} Pedido;

// Estrutura da pilha
typedef struct {
    Pedido* topo;
    int tamanho;
} Pilha;

// Funções auxiliares de entrada
static void limparBuffer(void) {
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

static void lerString(char* str, int tamanho) {
    fgets(str, tamanho, stdin);
    str[strcspn(str, "\n")] = '\0';
    limparBuffer();
}

static int lerInteiro(const char* mensagem) {
    int valor;
    while (1) {
        printf("%s", mensagem);
        if (scanf("%d", &valor) == 1) {
            limparBuffer();
            return valor;
        }
        printf("Entrada inválida! Digite um número válido.\n");
        limparBuffer();
    }
}

// Funções de manipulação da pilha
Pilha* criarPilha(void) {
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    if (!p) {
        fprintf(stderr, "Erro ao alocar memória para a pilha!\n");
        exit(EXIT_FAILURE);
    }
    p->topo = NULL;
    p->tamanho = 0;
    return p;
}

Pedido* criarPedido(int numero, const char* cliente, const char* descricao, 
                    int quantidade, StatusPedido status) {
    Pedido* novo = (Pedido*)malloc(sizeof(Pedido));
    if (!novo) {
        fprintf(stderr, "Erro ao alocar memória para o pedido!\n");
        exit(EXIT_FAILURE);
    }
    
    novo->numero = numero;
    strncpy(novo->cliente, cliente, MAX_NOME - 1);
    strncpy(novo->descricao, descricao, MAX_DESCRICAO - 1);
    novo->quantidade = quantidade;
    novo->status = status;
    novo->proximo = NULL;
    
    return novo;
}

void push(Pilha* p, Pedido* novo) {
    if (!p || !novo) return;
    
    novo->proximo = p->topo;
    p->topo = novo;
    p->tamanho++;
}

Pedido* pop(Pilha* p) {
    if (!p || !p->topo) return NULL;
    
    Pedido* removido = p->topo;
    p->topo = removido->proximo;
    p->tamanho--;
    return removido;
}

Pedido* top(Pilha* p) {
    return p ? p->topo : NULL;
}

// Funções de busca e atualização
Pedido* buscarPedido(Pilha* p, int numero) {
    if (!p) return NULL;
    
    Pedido* atual = p->topo;
    while (atual) {
        if (atual->numero == numero) return atual;
        atual = atual->proximo;
    }
    return NULL;
}

void atualizarStatus(Pilha* p, int numero, StatusPedido novoStatus) {
    Pedido* pedido = buscarPedido(p, numero);
    if (pedido) {
        pedido->status = novoStatus;
        printf("Status do pedido %d atualizado com sucesso!\n", numero);
    } else {
        printf("Pedido não encontrado!\n");
    }
}

// Funções de exibição
const char* statusParaString(StatusPedido status) {
    switch (status) {
        case STATUS_PENDENTE: return "Pendente";
        case STATUS_EM_PREPARO: return "Em preparo";
        case STATUS_PRONTO: return "Pronto";
        case STATUS_ENTREGUE: return "Entregue";
        default: return "Desconhecido";
    }
}

void exibirPedido(const Pedido* p) {
    if (!p) {
        printf("Pedido não encontrado!\n");
        return;
    }
    printf("Pedido #%d | Cliente: %s | Prato: %s | Qtd: %d | Status: %s\n",
           p->numero, p->cliente, p->descricao, p->quantidade, statusParaString(p->status));
}

void listarPedidos(Pilha* p) {
    if (!p || !p->topo) {
        printf("Nenhum pedido cadastrado.\n");
        return;
    }
    
    Pedido* atual = p->topo;
    while (atual) {
        exibirPedido(atual);
        atual = atual->proximo;
    }
}

// Função de liberação de memória
void liberarPilha(Pilha* p) {
    if (!p) return;
    
    while (p->topo) {
        Pedido* temp = pop(p);
        free(temp);
    }
    free(p);
}

// Função para seleção de status
StatusPedido selecionarStatus(void) {
    printf("\nStatus do pedido:\n");
    printf("1 - Pendente\n");
    printf("2 - Em preparo\n");
    printf("3 - Pronto\n");
    printf("4 - Entregue\n");
    
    int opcao;
    do {
        opcao = lerInteiro("Escolha uma opção (1-4): ");
    } while (opcao < 1 || opcao > 4);
    
    return (StatusPedido)opcao;
}

int main(void) {
    Pilha* pilha = criarPilha();
    int opcao, numero, quantidade;
    char cliente[MAX_NOME], descricao[MAX_DESCRICAO];
    
    do {
        printf("\nSistema de Gerenciamento de Pedidos - Restaurante\n");
        printf("1 - Inserir Pedido\n");
        printf("2 - Buscar Pedido\n");
        printf("3 - Atualizar Status\n");
        printf("4 - Remover Pedido\n");
        printf("5 - Listar Pedidos\n");
        printf("6 - Exibir Topo da Pilha\n");
        printf("0 - Sair\n");
        
        opcao = lerInteiro("Escolha uma opção: ");
        
        switch (opcao) {
            case 1: {
                numero = lerInteiro("Número do Pedido: ");
                printf("Nome do Cliente: ");
                lerString(cliente, MAX_NOME);
                printf("Descrição do Prato: ");
                lerString(descricao, MAX_DESCRICAO);
                quantidade = lerInteiro("Quantidade: ");
                
                StatusPedido status = selecionarStatus();
                Pedido* novo = criarPedido(numero, cliente, descricao, quantidade, status);
                push(pilha, novo);
                printf("\nPedido #%d inserido com sucesso!\n", numero);
                break;
            }
            
            case 2: {
                numero = lerInteiro("Número do Pedido para buscar: ");
                Pedido* p = buscarPedido(pilha, numero);
                exibirPedido(p);
                break;
            }
            
            case 3: {
                numero = lerInteiro("Número do Pedido para atualizar: ");
                StatusPedido novoStatus = selecionarStatus();
                atualizarStatus(pilha, numero, novoStatus);
                break;
            }
            
            case 4: {
                Pedido* removido = pop(pilha);
                if (removido) {
                    printf("Pedido #%d removido com sucesso!\n", removido->numero);
                    free(removido);
                } else {
                    printf("Pilha vazia!\n");
                }
                break;
            }
            
            case 5:
                listarPedidos(pilha);
                break;
                
            case 6: {
                Pedido* topo = top(pilha);
                if (topo) {
                    printf("Topo da pilha: ");
                    exibirPedido(topo);
                } else {
                    printf("Pilha vazia!\n");
                }
                break;
            }
            
            case 0:
                printf("Saindo do sistema...\n");
                break;
                
            default:
                printf("Opção inválida! Escolha uma opção do menu.\n");
        }
    } while (opcao != 0);
    
    liberarPilha(pilha);
    return 0;
}