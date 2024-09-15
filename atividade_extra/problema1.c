#include <stdio.h>
#include <stdlib.h>
int main(){
    int vetor[6], x=0;
    scanf("%d", &x);
    if (x %2==0)
    {
        x++;
    }
    
    for (int i = 0; i < 6; i++)
    {
        if (x % 2!=0)
        {
            vetor[i]=x;
            x+=2;
        }
        
    }
    for (int i = 0; i < 6; i++)
    {
        printf("%d\n", vetor[i]);
    }
    
    
}