#include <stdio.h>
int main(){
    float pi, pf, an, tc;
    printf("insira a população inicial, a população final e o número de anos:\n");
    scanf("%f %f %f", &pi, &pf, &an);
    tc=((pf-pi)/pi)*100/an;
    printf("a Taxa de Crescimento é: %.2f\n", tc);
    return 0;

}