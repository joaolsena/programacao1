#include <stdio.h>
int main(){
    int n, i, s=0;
    printf("insira um numero\n");
    scanf("%d", &n);
    for (i = 1; i <= n; i++)
    {
        if (n %i==0){
            s++;
        } 

    }
    if(s==2){
        printf("é um numero primo\n");
    } else {
        printf("nao é um numero primo\n");
    }
    return 0;
    
}