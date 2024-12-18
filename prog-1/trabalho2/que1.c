#include <stdio.h>
int main() { 
int n1;
printf("insira um número inteiro\n");
scanf("%d", &n1);
 if (n1>0){
    printf("o número é positivo\n");
 } else { if (n1<0) {
printf(" o número é negativo\n");
} else {
printf("o número é zero\n");
}
 }
return 0;
}