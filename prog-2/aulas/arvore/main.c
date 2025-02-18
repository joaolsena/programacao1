#include <stdio.h>
#include <stdlib.h>
#include "arvore2_3.h"

int main(){
    arvore2_3 arv;
    arv.raiz =NULL;
    int opcao;
    do
    {
        printf("digite o  valor a ser inserido ou 0 para finalizar:  ");
        scanf("%d", &opcao);
        if(opcao !=0)
        inserir (&arv, opcao);
        printf("\n\tarvore 2 3\n\n");
        imprimir(arv.raiz, 0);
        printf("\n");
    } while (opcao !=0);


    imprimir(arv.raiz, 0);
    printf("quantidade de chaves: %d\n", quantidadeChaves(arv.raiz));
    
    do
    {
        printf("digite o valor a ser buscado ou 0 para finalizar:  ");
        scanf("%d", &opcao);
         if(opcao !=0)
         buscar(arv.raiz, opcao, 0);
    } while (opcao !=0);
return 0;
}