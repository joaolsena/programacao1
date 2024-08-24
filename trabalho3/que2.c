#include <stdio.h>
#include <stdlib.h>



void pira(int alt){
if (alt<2) {  // se ela for menor que 2 vai dar erro
	perror("altura invalida");
	exit(1);
}

for (int i = 1; i <= alt; i++) // define as linhas da minha piramide 
{
	for (int f=(alt*2)-(2*i);f>=0; f--) printf("  "); // vai dar espaco e centralizar ela
	for (int j = 1; j <=i; j++){ // vai imprimir todos os numeros ate i
		printf("%4d", j);
		if(j==i){   
			for (int l = j-1; l>=1; l--){ // vai imprimir os numeros decrescentes
				printf("%4d", l);
			}
			
		}
		
	

}
putchar('\n');
}
}

int main(){
	int a=1;
	do
	{
		if(a < 0)
		printf("ta negativo, filho\n");
		else if (a >30)
		{
			printf("muito grande\n");
		}
		printf("insira a altura da piramide entre 1 e 30\n");
		scanf("%d", &a);
		
	} while (a <= 0 || a > 30);
	pira(a);
	
}
