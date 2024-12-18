#include <stdio.h>
int main(){
    float m, p;
    printf("insira a distancia em metros\n ");
    scanf("%f",&m);
    p=m* 3.28084;
    printf("a distancia em pes fica: %.2f\n", p);
    return 0;
}