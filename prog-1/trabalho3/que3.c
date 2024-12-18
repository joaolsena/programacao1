#include <stdio.h>
#include <stdlib.h>
void losa(int lar){
    if (lar %2 !=0)
    {
       for ( int i = 1; i <= lar; i+=2)
       {
        for (int k = (lar-i)/2; k>=0; k--) printf(" ");
        for (int j = 1; j <=i; j++)
        {
            printf("x");
        }
        putchar('\n');
       }

       for ( int i = lar-2; i >= 1; i-=2)
       {
        for (int k = (lar-i )/2; k>=0; k--) printf(" ");
        for (int j = 1; j <=i; j++)
        {
            printf("x");
        }
        putchar('\n');
       }
       
    } else {
         for ( int i = 2; i <= lar; i+=2)
       {
        for (int k = (lar-i)/2; k>=0; k--) printf(" ");
        for (int j = 1; j <=i; j++)
        {
            printf("x");
        }
        putchar('\n');
       }

       for ( int i = lar-2; i >= 2; i-=2)
       {
        for (int k = (lar-i )/2; k>=0; k--) printf(" ");
        for (int j = 1; j <=i; j++)
        {
            printf("x");
        }
        putchar('\n');
       }

    }  
    
}
int main(){
    int l=1;
    do
	{
		if(l < 1)
		printf("tem que ser maior que 1, filho\n");
		else if (l >30)
		{
			printf("muito grande\n");
		}
		printf("insira a largura central do losango entre 1 e 30\n");
		scanf("%d", &l);
		
	} while (l <= 0 || l > 30);
	losa(l);
    return 0;
}