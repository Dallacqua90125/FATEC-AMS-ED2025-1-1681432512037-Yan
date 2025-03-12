/----------------------------------------------------------------------------------/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: S1-B1-2                                 */
/*             Objetivo: <<  Manipulacao de Array com ponteiro  >>                  */
/*                                                                                  */
/*                                  Autor: Yan Rogério Dall'Acqua Rodrigues                  */
/*                                                                   Data:10/03/2024*/
/----------------------------------------------------------------------------------/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALUNOS 50
#define MAX_TAMANHO_NOME 50

typedef struct Aluno {
    char nomeAluno[MAX_TAMANHO_NOME];
    float provaEscrita[4], analiseCurricular[5], provaPratica[10], entrevista[3];
    float notaFinal;
    struct Aluno *proximoAluno;
} Aluno;

void coletarNotas(float *notas, int quantidadeNotas, const char *descricao) {
    printf("Digite as %d notas para %s:\n", quantidadeNotas, descricao);
    for (int i = 0; i < quantidadeNotas; i++) {
        printf("Nota %d: ", i + 1);
        scanf("%f", &notas[i]);
    }
}

float calcularNotaFinalAluno(float *notas, int quantidadeNotas) {
    float soma = 0.0, maiorNota = notas[0], menorNota = notas[0];

    for (int i = 1; i < quantidadeNotas; i++) {
        if (notas[i] > maiorNota) maiorNota = notas[i];
        if (notas[i] < menorNota) menorNota = notas[i];
    }

    for (int i = 0; i < quantidadeNotas; i++) {
        soma += notas[i];
    }

    return (soma - maiorNota - menorNota) / (quantidadeNotas - 2);
}

void obterNomeAluno(Aluno *novoAluno) {
    getchar();
    printf("\nDigite o nome do aluno: ");
    fgets(novoAluno->nomeAluno, sizeof(novoAluno->nomeAluno), stdin);
    novoAluno->nomeAluno[strcspn(novoAluno->nomeAluno, "\n")] = '\0';
}

void calcularNotaFinal(Aluno *novoAluno) {
    float provaEscrita = calcularNotaFinalAluno(novoAluno->provaEscrita, 4);
    float analiseCurricular = calcularNotaFinalAluno(novoAluno->analiseCurricular, 5);
    float provaPratica = calcularNotaFinalAluno(novoAluno->provaPratica, 10);
    float entrevista = calcularNotaFinalAluno(novoAluno->entrevista, 3);

    novoAluno->notaFinal = (provaEscrita * 0.3) + (analiseCurricular * 0.1) + (provaPratica * 0.4) + (entrevista * 0.2);
}

void adicionarAluno(Aluno **listaAlunos, int *quantidadeAlunos) {
    if (*quantidadeAlunos >= MAX_ALUNOS) {
        printf("Limite máximo de alunos atingido!\n");
        return;
    }

    Aluno *novoAluno = (Aluno *)malloc(sizeof(Aluno));
    if (!novoAluno) {
        printf("Erro ao alocar memória!\n");
        return;
    }

    obterNomeAluno(novoAluno);

    coletarNotas(novoAluno->provaEscrita, 4, "Prova Escrita");
    coletarNotas(novoAluno->analiseCurricular, 5, "Análise Curricular");
    coletarNotas(novoAluno->provaPratica, 10, "Prova Prática");
    coletarNotas(novoAluno->entrevista, 3, "Entrevista");

    calcularNotaFinal(novoAluno);

    novoAluno->proximoAluno = *listaAlunos;
    *listaAlunos = novoAluno;
    (*quantidadeAlunos)++;
}

void ordenarAlunos(Aluno **listaAlunos) {
    if (!*listaAlunos) return;

    int trocado;
    Aluno **ptr1, *tempAluno;

    do {
        trocado = 0;
        ptr1 = listaAlunos;

        while ((*ptr1) && (*ptr1)->proximoAluno) {
            if ((*ptr1)->notaFinal < (*ptr1)->proximoAluno->notaFinal) {
                tempAluno = (*ptr1)->proximoAluno;
                (*ptr1)->proximoAluno = tempAluno->proximoAluno;
                tempAluno->proximoAluno = *ptr1;
                *ptr1 = tempAluno;
                trocado = 1;
            }
            ptr1 = &((*ptr1)->proximoAluno);
        }
    } while (trocado);
}

void mostrarClassificacao(Aluno *listaAlunos) {
    printf("\nClassificação Final:\n");
    int posicao = 1;
    Aluno *atual = listaAlunos;

    while (atual != NULL && posicao <= 5) {
        printf("%dº Lugar: %s - Nota Final: %.2f\n", posicao, atual->nomeAluno, atual->notaFinal);
        atual = atual->proximoAluno;
        posicao++;
    }
}

void liberarListaAlunos(Aluno *listaAlunos) {
    Aluno *atual = listaAlunos;
    while (atual != NULL) {
        Aluno *tempAluno = atual;
        atual = atual->proximoAluno;
        free(tempAluno);
    }
}

int main() {
    Aluno *listaAlunos = NULL;
    int quantidadeAlunos = 0;
    char resposta;

    do {
        adicionarAluno(&listaAlunos, &quantidadeAlunos);

        if (quantidadeAlunos >= MAX_ALUNOS) {
            printf("\nLimite de %d alunos atingido. Encerrando entrada.\n", MAX_ALUNOS);
            break;
        }

        printf("\nDeseja adicionar outro aluno? (s/n): ");
        scanf(" %c", &resposta); 
    } while ((resposta == 's' || resposta == 'S') && quantidadeAlunos < MAX_ALUNOS);

    ordenarAlunos(&listaAlunos);
    mostrarClassificacao(listaAlunos);
    liberarListaAlunos(listaAlunos);

    return 0;
}