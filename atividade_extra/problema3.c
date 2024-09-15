#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main(){
    int n=0, *x;
    do
    {
        scanf("%d", &n);
        if(n>9999){
            perror("valor maximo é: 9999");
        }
    } while (n>9999);

    x=(int*) malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        do
        {
            scanf("%d", &x[i]);
            if (x[i]>pow(10, 7) || x[i]<pow(-10, 7))
            {
                perror("valor invalido");
            }
            

        } while (x[i]>pow(10, 7) || x[i]<pow(-10, 7));
        
        
      
    }
    for (int i = 0; i <n; i++)
    {
        if(x[i]==0){
            printf("NULL\n");
        } else{
    if(x[i] %2 !=0){
        printf("ODD ");
    } else {
    printf("EVEN ");
    }
    if (x[i]>0)
    {
        printf("POSITIVE\n");
    } else{
        printf("NEGATIVE\n");
    }
        }

    }
    free(x);
    return 0;
    

 }
    
    




