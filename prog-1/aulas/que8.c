#include <stdio.h>
int main(){
    int atual, a=0, b=1, n=0;
    printf("insira a sequencia de fibanacci que voce quer: ");
    scanf("%d", &n);
    for (int i =0; i < n; i++)
    {
        if(i<=1)
        atual=i;
        else{
            atual=a+b;
            a=b;
            b=atual;
        }

        printf("%d", atual);

    }
    printf("\n");
    
}