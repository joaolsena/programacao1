#include <stdio.h>
#include <math.h>
int main(){
    float pi, pf, tc;
    printf("insira  a taxa de juros nominal e o número de períodos por ano:\n");
    scanf("%f %f", &pi, &pf);
    tc=pow((1+pi/pf),pf)-1;
    printf("a Taxa Efetiva é: %.4f\n", tc );
    return 0;
}