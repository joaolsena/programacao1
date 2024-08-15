#include <stdio.h> 
#include <math.h>
int main(){
    float v, r, h, pi=M_PI;
    printf("insira o raio da base do cone:\n");
    scanf("%f", &r);
    printf("insira a altura do cone:\n");
    scanf("%f", &h);
    v=(1.0/3.0)*pi*pow(r,2)*h;
    printf("o volume do cone é: %.2f\n", v);
    return 0;

}