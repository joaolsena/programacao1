#include <stdio.h> 
#include <math.h>
int main(){
    float v, r, h, pi=M_PI;
    printf("insira o raio da base do cilindro:\n");
    scanf("%f", &r);
    printf("insira a altura do cilindro:\n");
    scanf("%f", &h);
    v=pi*pow(r,2)*h;
    printf("o volume do cilindro é: %.2f\n", v);
    return 0;

}