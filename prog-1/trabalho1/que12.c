#include <stdio.h>
#include <math.h>
int main(){
    float co,ca,h;
    printf("coloque a distancia em metros do primeio cateto\n");
    scanf("%f", &co);
    printf("coloque a distancia em metros do segundo cateto\n");
    scanf("%f", &ca);
    h= sqrt((co*co)+(ca*ca));
    printf("a hipotenusa do triangulo retangulo é %.2f\n",h);
    return 0;
}