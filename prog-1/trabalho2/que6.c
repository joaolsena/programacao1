#include <stdio.h>
int main () {
    int n;
    printf("insira um numero\n");
    scanf("%d", &n);
    if (n>=1 && n<=100) {
        printf("ele esta entre 1 e 100\n");
    } else {
        printf("nao esta entre 1 e 100\n");
    }
    return 0;
}