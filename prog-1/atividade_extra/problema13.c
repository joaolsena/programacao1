#include <stdio.h>
#include <stdlib.h>
int main(){
    int n=0, a=1, b=0, c=0, v[40], g;
    do
    {
    scanf("%d", &n);
    if(n<1 || n>40)
    printf("numero invalido\n");
      
    } while (n<1 || n>40);

    for (int i = 0; i < n; i++)
    {
        c=a+b;
        b=a;
        a=c;
        v[i]=b;
        
    }
    for (int i = n; i >0; i--)
    {
        g=n+1;
        g-=n;
        if(i!= g)
        printf("%d ", v[i-1]);
        else
        printf("%d", v[i-1]);
    }
    putchar('\n');
   
}