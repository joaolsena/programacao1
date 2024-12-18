#include <stdio.h>
int main() {
   float c,f;
   printf("insira a temperatura em graus celsius:\n");
   scanf("%f", &c);
   f=c*9/5+32;
   printf("a temperatura em Fahrenheit é %.2f\n", f);
   return 0;
}