#include <stdio.h>
int main(){
    float r, p;
    printf("insira o raio do circulo:\n");
    scanf("%f", &r);
    p=2*3.14*r;
    printf("o perimetro do circulo com raio de %.2f é igual a %.2f\n", r,p);
    return 0;

}