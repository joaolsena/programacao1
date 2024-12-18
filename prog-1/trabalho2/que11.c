#include <stdio.h>
int main(){
int a,b,c;
printf("insira os tres lados do triangulo\n");
scanf("%d %d %d", &a, &b, &c);
if (a+b>c && a+c>b && b+c>a) {
    printf(" é um triangulo\n");
printf("\n============= tipo de triangulo==============\n");
if (a==b && b==c) {
    printf("equilátero\n");
} else if (a==b || a==c || b==c) {
    printf("isóselis\n");
} else  {
    printf("escaleno\n");
} 
} else {
    printf("nao é um triangulo\n");
}
return 0;
}