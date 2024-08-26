#include <stdio.h>
#include <stdbool.h>
void trian(int h, int p){

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            bool vazado = (i==j || j==0 || i== h-1);
            if(p==1){
            printf("*");
            } else {
                printf("%c", vazado ? '*' : ' ');
            }

        }
        printf("\n");
    }
    


}
int main(){
    int al=1, po=1;
    do
    {
        if(al<1){
            printf("tem que ser maior que 0.\n");

        } else if (al>30)
        {
            printf("muito grande\n");
        }
        printf("insira a altura do triangulo entre 1 e 30: ");
        scanf("%d", &al);
        
    } while (al<1 || al>30);
    while (1){
        printf("\ninsira uma opcao:\n1) preenchido\n2) vazado\nsua escolha:");
         scanf("%d", &po);
         if(po!=1 && po!=2){
            printf("\nnumero invalido\n");
         } else break;
    }
    trian (al, po);
}