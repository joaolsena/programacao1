#include <stdio.h>
int main(){
    float v1, tx, t, m;
    printf("insira o valor inicial do investimento:\n");
    scanf("%f", &v1);
    printf("insira a taxa de juros anual:\n");
    scanf("%f", &tx);
    printf ("insira o periodo do ivestimento:\n");
    scanf("%f", &t);
    m=v1*((1+tx/100)*(1+tx/100));
    printf("o montante final é:%.2f\n", m);
    return 0;
}