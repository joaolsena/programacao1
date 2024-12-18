#include <stdio.h>
int main(){
    float tr, t,p;
    printf("insira o trabalho realizado\n");
    scanf("%f",&tr);
    printf("insira o tempo gasto\n");
    scanf("%f", &t);
    p=tr/t;
    printf("a potencia é: %.2f\n", p);
    return 0;

}