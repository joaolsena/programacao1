#include <stdio.h>
#include <stdlib.h>
int main(){
    int n, retangulos=0,c, v, *vetor= NULL, contador=0;
    while (1)
    {
         scanf("%d", &n);
        if(n==0)
        break;
         vetor=(int*) realloc(vetor, (contador +1) * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &c, &v);
        retangulos+=v/2;   
    }
    vetor[contador]= retangulos/2;
     retangulos=0;
     contador++;
    }
      for (int i = 0; i < contador; i++){
    printf("%d\n", vetor[i]);
}
      free(vetor);
    return 0; 
}