#include <stdio.h>
#include <math.h>
int main() {
float m, v, ec;
printf("insira a massa do objeto;\n");
scanf("%f", &m);
printf("insira a velocidade do objeto\n");
scanf("%f", &v);
ec=(m*pow(v,2))/2;
printf("a energia cinetica do objeto é: %.2f\n", ec);
return 0;

}
