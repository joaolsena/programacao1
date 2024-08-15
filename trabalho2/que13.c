#include <stdio.h>
int main(){
    float n1, n2; 
    char p;
    printf("insira o primeiro numero:\n");
    scanf("%f", &n1);
    printf("insira a operaçao: +,-,*,/.\n");
    scanf("%s", &p);
    printf("insira o segundo numero:\n");
    scanf("%f", &n2);
    switch (p)
    {
    case '+':
        printf("%.2f+%.2f=%.2f\n", n1,n2,(n1+n2));
        break;
     case '-':
        printf("%.2f-%.2f=%.2f\n", n1,n2,(n1-n2));
        break;
    case '*':
        printf("%.2fx%.2f=%.2f\n", n1,n2,(n1*n2));
        break;
    case '/':
        printf("%.2f/%.2f=%.2f\n", n1,n2,(n1/n2));
        break;
    default:
    printf("escolheu a operacao errada");
        break;
    }
    return 0;
}