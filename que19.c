#include <stdio.h>
int main(){
    int n;
    printf("insira um numero inteiro\n");
    scanf("%d", &n);
    if (n>=0 && n<50){
        printf("esta mais proximo de 10\n");
    } else if (n>49 && n<500){
        printf("esta mais proximo de 100\n");
    } else {
        printf("esta mais proximo de 1000\n");
    }
    return 0;
}
