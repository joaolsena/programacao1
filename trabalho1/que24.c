#include <stdio.h>
int main(){
    float m,a,fr;
    printf("insira a massa do objeto\n");
    scanf("%f", &m);
    printf("insira a aceleracao do objeto:\n");
    scanf("%f",&a);
    fr=m*a;
    printf("a forca resultande do obejeto é: %.2f\n", fr);
    return 0;
}