#include <stdio.h>
int  main(){
    float vm, d,t;
    printf("insira a distancia percorrida em metros\n");
    scanf("%f", &d);
    printf("inisra o tempo em segundos\n");
    scanf("%f", &t);
    vm=d/t;
    printf("a velocidade media é: %.2fm/s\n",vm);
    return 0;
}