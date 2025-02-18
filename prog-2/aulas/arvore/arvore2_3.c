#include <stdio.h>
#include <stdlib.h>
#include "arvore2_3.h"

No* criarNo(){
    No *novo = malloc(sizeof(No));
    if(novo){
        novo->quantchaves = 0;
        novo->valores [0] = 0;
         novo->valores [1] = 0;
          novo->valores [2] = 0;
         novo->pai = NULL;
         novo->filhos [0] = NULL;
         novo->filhos [1] = NULL;novo->filhos [2] = NULL;
         novo->filhos [3] = NULL;
    }
    return novo;
}

// insercao
int ehFolha (No *no){
    if (no->filhos[0])
    return 0;
    else 
    return 1;   
}

No *escolheFilho(No *no, int valor){
    int i=0, tam =no->quantchaves;
    if(ehFolha(no))
    return no;
    while (i < tam && valor > no->valores[i])
    i++;
    return no->filhos[i];
}

void dividirRaiz(No *raiz){
    No *esquerda, *direita;
    esquerda = criarNo();
    direita = criarNo();
    if(esquerda && direita){
        esquerda->valores[0] = raiz->valores[0];
        esquerda->quantchaves++;
        esquerda->filhos[0] = raiz->filhos[0];
        esquerda->filhos[1] = raiz->filhos[1];
        esquerda->pai = raiz;
        //atualiza PAI DOS FILHOS SE EXISTIREM
        if(esquerda->filhos[0]){
            esquerda->filhos[0]->pai= esquerda;
            esquerda->filhos[1]->pai= esquerda;
        }
        direita->valores[0]= raiz->valores[2];
        direita->quantchaves++;
        direita->filhos[0] = raiz->filhos[2];
        direita->filhos[1] = raiz->filhos[3];
        direita->pai= raiz;
       if(direita->filhos[0]){
            direita->filhos[0]->pai= direita;
            direita->filhos[1]->pai= direita;
        }

        raiz->valores[0] = raiz->valores[1];
        raiz->valores[1] = 0;
         raiz->valores[2] = 0;
         raiz->quantchaves =1;
         raiz->filhos[0] = esquerda;
         raiz->filhos[1] = direita;
        raiz->filhos[2] = NULL;
        raiz->filhos[3] = NULL;


    }
    else
    printf("erro ao alocar meomoria dividir raiz");
}

void dividirFilho (No *raiz){
    No *pai = raiz->pai, *direita = criarNo();
    int i, tam;

    if (direita)
    {
        direita->valores[0] = raiz->valores[2];
        direita->quantchaves++;
        direita->filhos[0] = raiz->filhos[2];
         direita->filhos[1] = raiz->filhos[3];
         direita->pai = pai;
         if (direita->filhos[0]) {
           direita->filhos[0]->pai = direita;
           direita->filhos[1]->pai = direita;
         }

         tam = pai->quantchaves-1;

         if (raiz->valores[1] > pai->valores[tam]){
            pai->valores[tam+1] = raiz->valores[1];
            pai->quantchaves++;
            pai->filhos[tam+2] = direita;
         }else{
            for ( i = tam; i >=0; i--)
            {
                if (raiz->valores[1] < pai->valores[1]){
                    pai->valores[i+1] = pai->valores[i];
                    pai->filhos[i+2] = pai->filhos[i+1];
            }else
                break;    
         }
         i++;
         pai->valores[i] = raiz->valores[1];
         pai->quantchaves++;
         pai->filhos[i+1] = direita;
           
    }
    raiz->quantchaves =1;
    raiz->valores[1] = 0;
    raiz->valores[2] = 0;
    raiz->filhos[2] = NULL;
    raiz->filhos[3] = NULL;


    
}else
printf("erro ao alocar memoria em dividir filho\n");
}

void dividir(No *raiz){
    if(raiz->pai)
    dividirFilho(raiz);
    else
    dividirRaiz(raiz);
}

void ordenar(No *no){
    int i, j, aux;
    for ( i = 0; i < no->quantchaves-1; i++)
    {
        for ( j = i +1; j < no->quantchaves; j++)
        {
            if (no->valores[j] < no->valores[i])
            {
                aux = no->valores[i];
                no->valores[i] =  no->valores[j];
                no->valores[j] = aux;
            }
            
        }
        
    }
    
}

void inserirValor(No *raiz, int valor){
    No *aux = raiz;

    do
    {
        if (aux->quantchaves ==3) // alterar para a 2-3
        {
           dividir(aux);
           if(aux->pai)
           aux = aux->pai;
        }
        aux = escolheFilho(aux, valor);
    } while (ehFolha(aux)== 0 || aux->quantchaves ==3);

    aux->valores[aux->quantchaves] = valor;
    aux->quantchaves++;
    ordenar(aux);   
}

void inserir ( arvore2_3 *arv, int valor){
    if(arv->raiz){
        inserirValor(arv->raiz, valor);
    }else{
        arv->raiz = criarNo();
        arv->raiz->valores[0] = valor;
        arv->raiz->quantchaves++;
    }
}

void imprimir (No *raiz, int nivel){
    int i;
    if (raiz)
    {
        for ( i = 0; i < nivel; i++)
           printf("\t");
        printf(" nivel: %2d: %3d | %3d | %3d\n", nivel, raiz->valores[0], raiz->valores[1], raiz->valores[2]);
        i =0;
        while (i < 4 && raiz->filhos[i])
        {
           imprimir(raiz->filhos[i], nivel +1);
           i++;
        }
        
    }   
}

No* buscar(No *no, int valor, int nivel){
    int i;
    if (no)
    {
       for ( i = 0; i < no->quantchaves; i++)
       {
        if (no->valores[i] == valor)
        {
           printf("o elemento %d esta no nivel %d na posicao %d\n", valor, nivel, i);
           return no;
        }else if (valor < no->valores[i])
            break; 
       }
       return buscar(no->filhos[i], valor, nivel+1);
       
    }else
    printf("o elemento %d nao foi encontrado\n", valor);
    return NULL;
    
}

int quantidadeChaves(No *raiz){
    int chaves =0;
    if(raiz){
        chaves = raiz->quantchaves;
        chaves += quantidadeChaves(raiz->filhos[0]);
         chaves += quantidadeChaves(raiz->filhos[1]);
          chaves += quantidadeChaves(raiz->filhos[2]);
           chaves += quantidadeChaves(raiz->filhos[3]);
           return chaves;
    }
    return 0;
}

