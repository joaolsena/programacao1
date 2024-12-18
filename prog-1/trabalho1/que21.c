#include <stdio.h>
int main(){
    float k, m;
    printf("insira a distancia percorrida em quilometros:\n");
    scanf("%f",&k);
    m=k*0.621371;
    printf("a distancia em milhas é: %.2f\n", m);
    return 0;
}