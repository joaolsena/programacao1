#include <stdio.h>
#include <stdlib.h>
//Construa um Algoritmo que, para um grupo de 50 valores inteiros, determine:a) A soma dos números positivos; b) A quantidade de valores negativos
int main(){
    int soma_positivo, negativo, n[10];
    printf("digite 10 valores inteiros\n");
    for (int i = 0; i < 10; i++)
    {
        printf("valor %d: ", i+1);
        scanf("%d",  &n[i]);
    }
    for (int i = 0; i < 10; i++)
    {
       if (n[i]>0)
       {
        soma_positivo+= n[i];
       } else if (n[i]<0)
       {
        negativo++;
       }
       
       
    }
    printf("%d\n", soma_positivo);
    printf("%d\n", negativo);

    

    
}