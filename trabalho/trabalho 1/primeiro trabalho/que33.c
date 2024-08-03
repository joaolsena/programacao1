#include <stdio.h>
int main(){
    float pi, pf, an, tc;
    printf("insira  o valor inicial de um bem, seu valor residual e a vida útil em anos:\n");
    scanf("%f %f %f", &pi, &pf, &an);
    tc=(pi-pf)/an;
    printf("a Depreciação Anual é: %.2f\n", tc);
    return 0;

}