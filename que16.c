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
    if (imc<18.5) {
        printf("abaixo do peso\n");
    } else {
        if(imc>=18.5 && imc<=24.9) {
            printf("normal\n");
        } else {
            if (imc>=25 && imc<=29.9) {
                printf("sobrepeso\n");
            } else{
                printf("obeso\n");
            }
        }
    }
    return 0;
}