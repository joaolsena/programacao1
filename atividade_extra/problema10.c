#include <stdio.h>
#include <stdlib.h>
int main(){
    int n, j, z, v1[10000], a , b, c=0, v[10000], t=0, in;
    while (1)
    {

    scanf("%d", &n);
    if(n!=0){
     a=0;
     b=0;
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &j, &z);
        a+=j;
        b+=z;
        v1[c]= a-b;
        c++;

    }
    v[t]=n;
    t++;
    }else
    break;
    }
    in=0;
    for (int i = 0; i < t; i++)
    {
        printf("Teste %d\n", i+1);
    
    
    for (int j = 0; j <v[i]; j++)
    {
        printf("%d\n", v1[in]);
        in++;
    }
    putchar('\n');
    }
    
    
}