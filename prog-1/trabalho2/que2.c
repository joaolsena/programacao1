#include <stdio.h>
int main(){
    int n1;
    printf("insira um numero inteiro\n");
    scanf("%d", &n1);
    if (n1 %2 == 0) {
        printf("o numero é par\n");

    } else {
        printf(" o numero é impar\n");
    }
    return 0;
}