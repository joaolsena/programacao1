#include <stdio.h>
#include <math.h>
int main(){
    float pi, pf, an, tc;
    printf("insira  o valor futuro de um investimento, a taxa de juros e o número de períodos:\n");
    scanf("%f %f %f", &pi, &pf, &an);
    tc=pi/pow((1+pf/100),an);
    printf("o Valor Presente  é: %.2f\n", tc );
    return 0;

}