#include <stdio.h>
#include <math.h>
int main(){
    float mi,k,r;
    printf("insira a distancia percorrida em milhas\n");
    scanf("%f", &mi);
    k=mi/0.621371;
r=round(k);
    printf("a distancia em quilometro é: %.2f\n", r);
    return 0;
}