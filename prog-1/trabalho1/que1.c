#include <stdio.h>
int main(){
    int n1, n2, soma;
    printf("insira o primeiro numero\n");
    scanf("%d", &n1);
    printf("insira o segundo numero\n");
    scanf("%d", &n2);
    soma=n1+n2;
    printf("a soma de %d mais %d é igual a %d\n", n1, n2, soma);
    return 0;
}