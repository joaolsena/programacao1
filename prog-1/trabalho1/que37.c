#include <stdio.h>
int main (){
    float l, h,a;
    printf("insira  o valor da diagonal maior\n");
    scanf("%f", &l);
    printf("insira o valor da diagonal menor\n");
    scanf("%f", &h);
    a=(l*h)/2;
    printf("a area do losango é; %.2f\n",a);
    return 0;

}