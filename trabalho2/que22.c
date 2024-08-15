#include <stdio.h>
int main(){
    int tp, q;
    float d,pf;
    printf("\ninsira o produto que voce quer pelo o seu respectivo codigo:\n1: Produtos de tecnologia - R$150,00 cada\n2: Produtos de alimentação - R$50,00 cada\n3: Produtos de vestuário - R$80,00 cada\n4: Produtos de saúde - R$120,00 cada\n5: Produtos de lazer - R$90,00 cada\n");
    scanf("%d", &tp);
    printf("insira a quantidade de produto que voce quer\n");
    scanf("%d", &q);
    switch (tp)
    {
    case 1:
        pf=150*q;
        printf("valor sem desconto:R$%.2f\n", pf);
        if (q>=1 && q<=5){
            printf("o valor final com desconto é:R$%.2f\n", pf-pf*0.05);
        } else{
            if (q>5 && q<11) {
                printf("o valor final com desconto é:R$%.2f\n", pf-pf*0.1);
            } else {
                printf("o valor final com desconto é:R$%.2f\n", pf-pf*0.15);
            }
        }
        break;
        case 2:
         pf=50*q;
        printf("valor sem desconto:R$%.2f\n", pf);
        if (q>=1 && q<=5){
            printf("o valor final com desconto é:R$%.2f\n", pf-pf*0.05);
        } else{
            if (q>5 && q<11) {
                printf("o valor final com desconto é:R$%.2f\n", pf-pf*0.1);
            } else {
                printf("o valor final com desconto é:R$%.2f\n", pf-pf*0.15);
            }
        }
        break;
        case 3:
        pf=80*q;
        printf("valor sem desconto:R$%.2f\n", pf);
        if (q>=1 && q<=5){
            printf("o valor final com desconto é:R$%.2f\n", pf-pf*0.05);
        } else{
            if (q>5 && q<11) {
                printf("o valor final com desconto é:R$%.2f\n", pf-pf*0.1);
            } else {
                printf("o valor final com desconto é:R$%.2f\n", pf-pf*0.15);
            }
        }
        break;
        case 4:
        pf=120*q;
        printf("valor sem desconto:R$%.2f\n", pf);
        if (q>=1 && q<=5){
            printf("o valor final com desconto é:R$%.2f\n", pf-pf*0.05);
        } else{
            if (q>5 && q<11) {
                printf("o valor final com desconto é:R$%.2f\n", pf-pf*0.1);
            } else {
                printf("o valor final com desconto é:R$%.2f\n", pf-pf*0.15);
            }
        }
        break;
        case 5:
        pf=90*q;
        printf("valor sem desconto:R$%.2f\n", pf);
        if (q>=1 && q<=5){
            printf("o valor final com desconto é:R$%.2f\n", pf-pf*0.05);
        } else{
            if (q>5 && q<11) {
                printf("o valor final com desconto é:R$%.2f\n", pf-pf*0.1);
            } else {
                printf("o valor final com desconto é:R$%.2f\n", pf-pf*0.15);
            }
        }
        break;
    
    default:
    printf("codigo invalido\n");
        break;
    }
    return 0;
}