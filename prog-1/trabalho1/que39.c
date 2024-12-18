#include <stdio.h>
int main() {
    float nl,l,p;
    printf("insira o numero de lados e a medida de um lado:\n");
    scanf("%f %f", &nl, &l);
    p= nl*l;
    printf("o perimetro é: %.2f\n", p);
    return 0;
}