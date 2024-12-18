#include <stdio.h>
#include <stdlib.h>
int main(){
    int n, soma=0;
    do
    {
        printf("insira um numero para fazer a soma de 1 ate ele: ");
    scanf("%d", &n);
    if(n<1){
        perror("numero invalido");
    }
    } while (n<1);

    for (int i = 1; i <=n; i++)
    {
        soma+=i;
    }
    printf("a soma de 1 ate %d= %d\n", n, soma);
    
    
    
}