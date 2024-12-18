#include <stdio.h>

int main() {
	int parcela;
	printf("Digite o n de parcelas: ");
	scanf("%d", &parcela);
	int n1=0, n2=1;

	for(int i = 0; i < parcela; i++) {
		if(i % 2 == 0) printf("%d ", n1);
		else {
			printf("%d ", n2);

			n1 += n2;
			n2 += n1;
		}
	}
}
