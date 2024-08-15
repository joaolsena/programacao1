#include <stdio.h>
int main(){
    float m,v,d;
    printf("insira a massa do objeto\n");
    scanf("%f", &m);
    printf("insira o volume do obejto\n");
    scanf("%f", &v);
    d=m/v;
    printf("a densidade do objeto é:%.2f\n", d);
    return 0;
}