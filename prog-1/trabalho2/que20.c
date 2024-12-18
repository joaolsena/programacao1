#include <stdio.h>
int main  (){
    float n, v, b;
    printf("insira o nummero de horas que o carro ficou estacionado\n");
    scanf("%f", &n);
    if  (n<=2){
        v=n*5;
        printf("valor final: R$%.2f\n", v);
    } else {
        if (n>=3 && n<=5){
            b=n-2;
            v=10+(b*3);
            printf("valor final:R$%.2f\n",v);
        } else {
            if(n>=6) {
                b=n-5;
                v=19+(b*2);
                printf("valor final:R$%.2f\n", v);
            }
        }
    }
return 0;
}