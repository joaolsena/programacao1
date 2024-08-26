#include <stdio.h>
#include <stdlib.h>

void natal(int ba, int l, int h){

    for (int i = 0; i <ba; i+=2)
    {
        for(int k = (ba-i)/2; k>0; k--)
        putchar(' ');
        for (int j = 0; j <=i; j++)
        {
            putchar('*');
        }
        putchar('\n');
    }

    for (int i = 0; i < h; i++)
    {
      for (int k= (ba-l) /2; k > 0; k--) 
           putchar(' ');
      for (int j = 0; j < l; j++)
      {
        putchar('*');
      }
      putchar('\n');
    }
        
}
int main(){
    int c=1, la=1, al=1;

    do{
        printf("\ninsira a base da arvore com um numero impar, maior que 2 e menor que 60: ");
        scanf("%d", &c);
        if (c %2 == 0 || c<4 || c>60){
            printf("\npode somente numeros imapares e maiores que 2 e o tamanho maximo permitido é 60.\n");
        } 
    } while (c %2 == 0 || c<4 || c>60);
    
    while (1){
        printf("\ninsira a largura do tronco com um numero impar, maior que 0 e nao pode ultrapassar a metade da base da arvore: ");
        scanf("%d", &la);
        if(la %2 ==0 || la<1 || la>(c/2)){
            printf("\npode somente numeros impares, maior que 0 e nao pode ultrapassar a metade da base da arvore .\n");
        } else break;
    }
    while (1){
        printf("\ninsira a altura do troco com um numero maior que 1 e nao pode ultrapassar a metade da base da arvore: ");
        scanf("%d", &al);
        if(al<2 || al>(c/2)){
            printf("\npode somente numeros maiores que 1 e nao pode ultrapassar a metade da base da arvore.\n");

        }else break;
    } 
  natal(c,la, al);
}