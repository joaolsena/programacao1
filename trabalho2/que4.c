#include <stdio.h>
int main() {
    int i;
    printf("insira sua idade\n");
    scanf("%d", &i);
    if (i>=18) {
        printf(" voce esta apto para votar:)\n");
    } else {
        printf("voce nao esta apto para votar\n");
    }
    return 0;
}