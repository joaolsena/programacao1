#ifndef arvore2_3_H
#define arvore2_3_H

struct no
{
   int valores [3];
   struct no *filhos[4];
   struct no *pai;
   int quantchaves;
   
};
 typedef struct no No;
 
 struct arv
 {
    No *raiz;
 };
 
 typedef struct arv arvore2_3;

 No* criarNo();
 int ehFolha(No *no);
 void dividirRaiz(No *raiz);
 void dividirFilho (No *raiz);
 void dividir (No *raiz);
 void ordenar (No *no);
 void inserirValor (No *raiz, int valor);
 void inserir (arvore2_3 *arv, int valor);
 void imprimir (No *raiz, int nivel);
 No* buscar (No *no, int valor, int nivel);
 int quantidadeChaves (No *raiz);
 int getIndice (No *no, int valor);
 int getMaiorDosMenores (No *raiz);
 int getMenorDosMaiores (No *raiz);
 #endif