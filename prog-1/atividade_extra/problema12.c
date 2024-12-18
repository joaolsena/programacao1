#include <stdio.h>
#include <stdlib.h>
int main(){
    int d, l, x,f;
    scanf("%d %d %d %d", &d, &l, &x, &f);
    for (int i = 0; i < f; i++)
    {
        d++;
        if(d %2!=0)
        l-=x;
        else
        l+=x;
    }
    printf("%d\n", l);
    
}