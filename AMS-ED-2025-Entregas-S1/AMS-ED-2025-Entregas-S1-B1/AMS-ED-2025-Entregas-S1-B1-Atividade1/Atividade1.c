#include <stdio.h>

void CalcularPrecoComDesconto(float *valor, float percentual) {
    *valor -= (*valor * percentual / 100);
}

int main() {
    float valorOriginal, desconto, valorDesconto;

    printf("Informe o valor do produto: R$ ");
    scanf("%f", &valorOriginal);
    valorDesconto = valorOriginal;

    printf("Informe a porcentagem de desconto: ");
    scanf("%f", &desconto);

    CalcularPrecoComDesconto(&valorDesconto, desconto);

    printf("Valor inicial: R$ %.2f\n", valorOriginal);    
    printf("Desconto concedido: %.f%%\n", desconto);
    printf("Valor final com desconto: R$ %.2f\n", valorDesconto);

    return 0;
}
