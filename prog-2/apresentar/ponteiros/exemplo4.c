#include <stdio.h>

int main() {
    int vetor[5];  // Vetor de 5 inteiros
    int *p = vetor;  // Ponteiro para o início do vetor

    // Preencher o vetor com valores fornecidos pelo usuário
    printf("Digite 5 números inteiros:\n");
    for (int i = 0; i < 5; i++) {
        scanf("%d", p + i);  // Preenche o vetor utilizando o ponteiro
    }

    // Exibir os elementos do vetor
    printf("Os elementos do vetor são:\n");
    for (int i = 0; i < 5; i++) {
        printf("%d ", *(p + i));  // Acessa os elementos do vetor via ponteiro
    }
    printf("\n");

    return 0;
}
