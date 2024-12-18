#include <stdio.h>
#include <stdlib.h>
int main(){
    int atual, n=0, a=0, b=1, i=0;
    scanf("%d", &n);
    do
    {
        if(i<=1)
        atual=i;
        else{
            atual=a+b;
            a=b;
            b=atual;
        }
        printf("%d ", atual);
        i++;

    } while (i<n);
    printf("\n ");
}