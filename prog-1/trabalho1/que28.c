#include <stdio.h>
#include <math.h>
int main(){
    float v, r, pi= M_PI;
    printf("insira o raio da esfera:\n");
    scanf("%f", &r);
    v=(4.0/3.0)*pi*pow(r,3);
    printf("o volume da esfera é: %.2f\n", v);
    return 0;
}