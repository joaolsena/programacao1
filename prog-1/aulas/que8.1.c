#include <stdio.h>
#include <stdlib.h>
int main(){
    int atual, n, a=0 , b=1, i=0;
    scanf("%d", &n);
    while (i<n)
    {
        if(i<=1)
        atual=i;
        else{
            atual=a+b;
            a=b;
            b=atual;
        }

        printf("%d", atual);
        i++;
    }
    putchar('\n');
}