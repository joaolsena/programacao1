#include <stdio.h>
int main(){
    float n1,n2,n3,p1,p2,p3, mp;
    printf("insira a nota 1 e seu respectivo peso:\n");
    scanf("%f %f", &n1, &p1);
    printf("insira a nota 2 e seu respectivo peso:\n");
    scanf("%f %f", &n2, &p2);
    printf("insira a nota 3 e seu respectivo peso:\n");
    scanf("%f %f", &n3, &p3);
    mp=(n1*p1+n2*p2+n3*p3)/(p1+p2+p3);
    printf("a  media ponderada é: %.2f\n", mp);
    return 0;


}