#include <stdio.h>
int main(){
    float n;
    printf("insira o seu rendimento anual\n");
    scanf("%f", &n);
    if (n<=22000){
        printf("o valor final é:R$%.2f\n", (n*0.05));
    } else {
        if(n>22002 && n<=45000){
            printf("o valor final é:R$%.2f\n", (n*0.15));
        } else{
            printf("o valor final é:R$%.2f\n", (n*0.25));
        }
    }
    return 0;
}