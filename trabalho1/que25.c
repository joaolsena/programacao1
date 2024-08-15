#include <stdio.h>
int main(){
    float m,a,fr;
    printf("insira a força aplicada\n");
    scanf("%f", &m);
    printf("insira a distância percorrida:\n");
    scanf("%f",&a);
    fr=m*a;
    printf("o trabalho realizado é: %.2f\n", fr);
    return 0;
}