/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: S1-B1-4                                 */
/*             Objetivo: <<  Manipulação de Pilha - Implementado HP12c  >>          */
/*                                                                                  */
/*                                  Autor: Yan Rogério Dall'Acqua Rodrigues         */
/*                                                                   Data:01/04/2025*/
/*----------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 100
#define MAX_EXPR 256  

typedef struct {
    struct {
        double valor;
        char expressao[MAX_EXPR];
    } elementos[MAX_SIZE];
    int topo;
} Pilha;

void criar_pilha(Pilha *p) {
    p->topo = -1;
}

int vazia(Pilha *p) {
    return p->topo == -1;
}

int cheia(Pilha *p) {
    return p->topo == MAX_SIZE - 1;
}

void push(Pilha *p, double valor, const char *expressao) {
    if (cheia(p)) {
        printf("Erro: Pilha cheia!\n");
        return;
    }
    p->topo++;
    p->elementos[p->topo].valor = valor;
    strncpy(p->elementos[p->topo].expressao, expressao, MAX_EXPR - 1);
    p->elementos[p->topo].expressao[MAX_EXPR - 1] = '\0';
}

double pop(Pilha *p, char *expressao) {
    if (vazia(p)) {
        printf("Erro: Pilha vazia!\n");
        return 0;
    }
    double valor = p->elementos[p->topo].valor;
    strcpy(expressao, p->elementos[p->topo].expressao);
    p->topo--;
    return valor;
}

void calcular_rpn(const char *expressao) {
    Pilha pilha;
    criar_pilha(&pilha);
    
    char expressao_original[MAX_EXPR];
    strncpy(expressao_original, expressao, MAX_EXPR - 1);
    expressao_original[MAX_EXPR - 1] = '\0';

    char *token = strtok(strdup(expressao), " ");
    
    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            push(&pilha, atof(token), token);
        } else {
            if (pilha.topo < 1) {
                printf("Erro: Expressao invalida!\n");
                free(token);
                return;
            }

            char expr1[MAX_EXPR], expr2[MAX_EXPR];
            double b = pop(&pilha, expr2);
            double a = pop(&pilha, expr1);
            double resultado;
            char nova_expr[MAX_EXPR];

            switch (token[0]) {
                case '+': 
                    resultado = a + b;
                    snprintf(nova_expr, MAX_EXPR, "(%s + %s)", expr1, expr2);
                    break;
                case '-': 
                    resultado = a - b;
                    snprintf(nova_expr, MAX_EXPR, "(%s - %s)", expr1, expr2);
                    break;
                case '*': 
                    resultado = a * b;
                    snprintf(nova_expr, MAX_EXPR, "(%s * %s)", expr1, expr2);
                    break;
                case '/':
                    if (b == 0) {
                        printf("Erro: Divisao por zero!\n");
                        free(token);
                        return;
                    }
                    resultado = a / b;
                    snprintf(nova_expr, MAX_EXPR, "(%s / %s)", expr1, expr2);
                    break;
                default:
                    printf("Erro: Operador invalido!\n");
                    free(token);
                    return;
            }

            push(&pilha, resultado, nova_expr);
        }
        token = strtok(NULL, " ");
    }
    
    if (pilha.topo != 0) {
        printf("Erro: Expressao invalida!\n");
        return;
    }
    
    char expressao_final[MAX_EXPR];
    double resultado_final = pop(&pilha, expressao_final);

    printf("==============================================\n");
    printf("Expressao RPN:       %s\n", expressao_original);
    printf("Expressao Algebrica: %s\n", expressao_final);
    printf("Resultado: %.2f\n", resultado_final);
}

int main() {
    char expressao[MAX_EXPR];

    while (1) {
        printf("Digite a expressao RPN (ou 'sair' para encerrar): ");
        if (fgets(expressao, sizeof(expressao), stdin) == NULL) {
            printf("Erro na leitura da entrada.\n");
            break;
        }
        expressao[strcspn(expressao, "\n")] = 0;

        if (strcmp(expressao, "sair") == 0) {
            printf("Encerrando a calculadora...\n");
            break;
        }

        calcular_rpn(expressao);
    }

    return 0;
}