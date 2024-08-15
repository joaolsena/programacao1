#include <stdio.h>
#include <math.h>
int main(){
    float pi=3.14159, r, h, v;
    printf("insira a altura e o raio do cilindro:\n");
    scanf("%f %f", &h, &r);
    v=pi*pow(r,2)*h;
    printf("o volume do cilindro é %.3F\n", v);
    return 0;
}