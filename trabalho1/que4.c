#include <stdio.h>
int main (){
    float l, h,a;
    printf("insira a largura do triangulo\n");
    scanf("%f", &l);
    printf("insira a altura do triangulo\n");
    scanf("%f", &h);
    a=l*h;
    printf("um triangulo com largura %.2f e altura %.2f tem uma area de %.2f\n", l,h,a);
    return 0;




}