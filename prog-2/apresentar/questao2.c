#include <stdio.h>

int main() {
    int vetor[10];
    int *p = vetor;  // Ponteiro para o início do vetor
    int soma = 0;

    // Preencher o vetor com valores fornecidos pelo usuário
    printf("Digite 10 números inteiros:\n");
    for (int i = 0; i < 10; i++) {
        scanf("%d", p + i);  // Preenche o vetor utilizando o ponteiro
    }

    // Exibir os elementos do vetor
    printf("Os elementos do vetor são:\n");
    for (int i = 0; i < 10; i++) {
        printf("%d ", *(p + i));  // Acessa os elementos do vetor via ponteiro
    }
    printf("\n");

    // Calcular a soma dos elementos do vetor
    for (int i = 0; i < 10; i++) {
        soma += *(p + i);  // Soma os elementos utilizando o ponteiro
    }

    // Exibir a soma
    printf("A soma dos elementos do vetor é: %d\n", soma);

    return 0;
}
