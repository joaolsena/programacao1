#include <stdio.h>
#include <stdlib.h>
int main(){
    int n,h, v[250], menor[100], maior[100];
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &h);
        v[i]=h;
        if(v[1]>v[i])
        menor[i]=v[i];
        else
        maior[i]= v[i];


    }
    
    
}