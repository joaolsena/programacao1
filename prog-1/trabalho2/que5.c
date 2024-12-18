#include <stdio.h>
int main() {
    int n;
    printf("insira um numero inteiro\n");
    scanf("%d", &n);
    if (n %5 ==0) {
        printf("ele é mutiplo de 5\n");
    } else {
        printf("nao é mutiplo de 5\n");
    }
    return 0;
}