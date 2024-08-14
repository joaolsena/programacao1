#include <stdio.h>
int main() {
    int n;

    printf("insira a sua velocidade em km/h\n");
    scanf("%d", &n);
    if (n<30) {
        printf("baixa\n");
    } else if (n>=30 && n<=60) {
        printf("media\n");
    } else if (n>60) {
        printf("alta\n");
    }
    return 0;
}