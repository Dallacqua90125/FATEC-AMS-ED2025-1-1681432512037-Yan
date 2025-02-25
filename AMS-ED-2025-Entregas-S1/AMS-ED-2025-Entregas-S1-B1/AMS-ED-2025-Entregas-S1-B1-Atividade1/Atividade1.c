void CalcularPrecoComDesconto(float *valor, float percentual) {
    *valor -= (*valor * percentual / 100);
}

int main() {
    float valorOriginal;
    float percentualDesconto;

    printf("Informe o valor do produto: R$ ");
    scanf("%f", &valorOriginal);

    printf("Informe a porcentagem de desconto: ");
    scanf("%f", &percentualDesconto);

    printf("Valor inicial: R$ %.2f\n", valorOriginal);

    CalcularPrecoComDesconto(&valorOriginal, percentualDesconto);

    printf("Desconto concedido: %.f%%\n", percentualDesconto);
    
    printf("Valor final com desconto: R$ %.2f\n", valorOriginal);

    return 0;
}
