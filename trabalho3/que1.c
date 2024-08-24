#include <stdio.h>
#include <stdlib.h>
int main(){
    int n,v=1;
    do{
    printf ("insira a altura do triangulo de pascal entre 1 e 25\n");
    scanf("%d", &n);
    if (n<1 || n>25){
      printf("numero invalido. tente novamente\n");
    } 
    }while (n<1 || n>25);
    for (int i =0 ; i<n; i++) //linhas do tri
    {
      for (int f= n-i; f>=0; f--) printf("  "); //epaçamento do tri
      v=1; // vai sempre imprimir 1
       for (int j = 0; j<=i; j++) //numeros que vao aparecer em i
       {
      printf("%3d ", v);
      v=(v*(i-j)/(j+1));
       }       
       printf("\n");
    }
    return 0;
}

