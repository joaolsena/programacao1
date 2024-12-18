#include <stdio.h>
#include <stdlib.h>
int main(){
    int h, m, o, vetor1[3],v2[3], v3[3], n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d %d", &h, &m, &o);
        vetor1[i]= h;
        v2[i]=m;
        v3[i]=o;

    }
    for (int i = 0; i < n; i++)
    {
        if(v3[i]==1)
        printf("%02d:%02d - A porta abriu!\n", vetor1[i], v2[i]);
        else {
            printf("%02d:%02d - A porta fechou!\n", vetor1[i], v2[i]);

        }
    }
    

}