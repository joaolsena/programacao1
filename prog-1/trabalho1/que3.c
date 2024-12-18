#include <stdio.h>
int main(){

    int n1,n2,n3,m;
    printf("insira o primeiro numero:\n");
    scanf("%d", &n1);
    printf("insira segundo numero:\n");
    scanf("%d", &n2);
    printf("insira terceiro numero:\n");
    scanf("%d", &n3);
    m=(n1+n2+n3)/3;
    printf("a média entre os numeros %d,%d,%d, é igual a %d\n", n1,n2,n3,m);
    return 0;

}