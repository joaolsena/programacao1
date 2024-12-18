#include <stdio.h>
int main(){
    float v1, tx, t, js;
    printf("insira o valor inicial do investimento:\n");
    scanf("%f",&v1);
    printf("insira a taxa de juros anual em numero inteiro:\n");
    scanf("%f", &tx);
    printf("insira o tempo do investimento em anos:\n");
    scanf("%f",&t);
    js=v1*(tx/100)*t;
    printf("o montante de juros simples acumulado no final do periodo é:%.2f\n", js);
    return 0;
}