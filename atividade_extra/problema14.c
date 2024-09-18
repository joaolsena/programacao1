#include <stdio.h>
#include <stdlib.h>
int main(){
    // 4 10 10 10 10= -3 10 10 10 10=37
    // 10 4 4 4 4 4 4 4 4 4 4= -9 4...=31
    int k, n, o, soma=0, v[20];
    
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
         soma=0;
        scanf("%d", &k);
        for (int j= 0; j < k; j++)
        {
            scanf("%d", &o);
            soma+=o;
        }
        soma-= k-1;
        v[i]=soma;
    }
    for (int i = 0; i < n; i++)
    {
        printf("%d\n", v[i]);
    }

}