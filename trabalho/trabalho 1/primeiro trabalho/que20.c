#include <stdio.h>
int  main(){
    float vm, d,t;
    printf("insira a força aplicada em newtons \n");
    scanf("%f", &d);
    printf("inisra  a área em metros quadrados\n");
    scanf("%f", &t);
    vm=d/t;
    printf("a presao é: %.2f\n",vm);
    return 0;
}