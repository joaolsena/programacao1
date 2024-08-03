#include <stdio.h>
int main(){
    float r,a;
    printf("insira o raio do circulo:\n");
    scanf("%f", &r);
    a=r*3.14*r;
    printf("a area do circulo com o raio %.2f é igual a %.2f\n",r,a);
    return 0;
}