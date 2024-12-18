#include <stdio.h>
#include <math.h>
int main(){
    float v, a;
    printf("insira a aresta do cubo:\n");
    scanf("%f", &a);
    v=pow(a,3);
    printf("o volume do cubo é: %.2f\n", v);
    return 0;
}