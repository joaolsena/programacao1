#include <stdio.h>
int main(){
    float n;
    printf("insira o valor da compra\n");
    scanf("%f", &n);
    if (n<=100){
        printf("o valor final é: %.2f\n", (n*0.05)+n);
    } else {
        if(n>100 && n<=500){
            printf("o valor final é:%.2f\n", (n*0.1)+n);
        } else{
            printf("o valor final é: %.2f\n", (n*0.15)+n);
        }
    }
    return 0;
}