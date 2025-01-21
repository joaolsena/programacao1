#include <stdio.h>

void imprime(char *v, int n) {
    for (char *c = v; c < v + n; c++) {
        printf("%c", *c);
    }
}

int main() {
    char texto[20];
    int n;

    // Lê uma string
    printf("Digite o texto: ");
    scanf("%19s", texto); // Limite de 19 caracteres para evitar buffer overflow

    // Define o número de caracteres a serem impressos
    printf("Digite o número de caracteres a imprimir: ");
    scanf("%d", &n);

    
    imprime(texto, n);

    return 0;
}
