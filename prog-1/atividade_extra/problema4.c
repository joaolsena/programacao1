#include <stdio.h>
#include <stdlib.h>
int main(){
    int n[10], y[10], v, x=1;
    do
    {
       scanf("%d", &v);
       if(v>50){
        fprintf(stderr, "numero invalido!\n");
       }
    } while (v>50);
    

    for (int i = 0; i < 10; i++)
    {
        n[i]= v;
        v=v*2;

    }
    for (int i = 0; i < 10; i++)
    {
       printf("N[%d] = %d\n", i, n[i]);
    }
    
}