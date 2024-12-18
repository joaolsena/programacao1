#include <stdio.h>
#include <stdlib.h>
int main(){
    int n=0;
    do
    {
        scanf("%d", &n);
        if(n<6 || n>1998){
            perror("numero invalido");
        }
    } while (n<6 ||n>1999);
    for (int i = 2; i <=n; i+=2)
    {
        printf("%d^2 = %d\n", i, i*i);
    }
    
    return 0;
    
}