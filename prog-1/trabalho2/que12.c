#include <stdio.h>
int main() {
    int n;
    printf("insira o ano\n");
    scanf("%d", &n);
    if((n %4==0 && n %100!=0)|| n %100==0) {
        printf("o ano é bissexto\n");
    } else {
        printf("o ano nao é bissexto\n");
    }
    return 0;
}