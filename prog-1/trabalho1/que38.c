#include <stdio.h>
int main(){
    float pf, pp, d;
    printf("insira o preco do produto e o desconto em porcentagem:\n");
    scanf("%f %f", &pp, &d);
    pf=pp*(1-d/100);
    printf("o preco final é: %.2f\n", pf);
    return 0;
}