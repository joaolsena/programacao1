#include <stdio.h>
int main(){
    float n1, n2; 
    int p;
    printf("insira o primeiro numero:\n");
    scanf("%f", &n1);
    printf("insira a operaçao\n1=+\n2=-\n3=*\n4=/\n");
    scanf("%d", &p);
    printf("insira o segundo numero:\n");
    scanf("%f", &n2);
    switch (p)
    {
    case 1:
        printf("%.2f+%.2f=%.2f\n", n1,n2,(n1+n2));
        break;
     case 2:
        printf("%.2f-%.2f=%.2f\n", n1,n2,(n1-n2));
        break;
    case 3:
        printf("%.2fx%.2f=%.2f\n", n1,n2,(n1*n2));
        break;
    case 4:
        printf("%.2f/%.2f=%.2f\n", n1,n2,(n1/n2));
        break;
    default:
    printf("escolheu a operacao errada");
        break;
    }
    return 0;
}