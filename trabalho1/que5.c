#include <stdio.h>
int main(){
    float b,h,a;
    printf("insira a base do trinagulo\n");
    scanf("%f", &b);
    printf("insira a altura do trinagulo\n");
    scanf("%f", &h);
    a=(b*h)/2;
    printf("a area de um triangulo com base %.2f e altura de %.2f é igual a %.2f\n", b,h,a);
return 0;
}