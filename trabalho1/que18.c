#include <stdio.h>
#include <math.h>
int main(){
    float p,a,imc;
    printf("insira seu peso em quilogramas\n");
    scanf("%f", &p);
    printf("insira sua altura em metros\n");
    scanf("%f", &a);
    imc=p/pow(a,2);
    printf("seu imc é:%.2f\n", imc);
    return 0;
}