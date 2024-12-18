#include <stdio.h>

#define TAM_M 5

int main() {

	int matriz[TAM_M][TAM_M];

	for(int i = 0; i < TAM_M; i++) {
		for(int j = 0; j < TAM_M; j++) {
			scanf("%d", &matriz[i][j]);
		}
	}

	int soma_l4 = 0;
	int soma_c2 = 0;
	int soma_dp = 0;
	int soma_ds = 0;
	int soma_t = 0;

	for(int i = 0; i < TAM_M; i++) {
		soma_l4+=matriz[4][i];
		soma_c2+=matriz[i][2];
		soma_dp+=matriz[i][i];
		soma_ds+=matriz[i][TAM_M-i-1];

		for(int j = 0; j < TAM_M; j++) {
			soma_t+=matriz[i][j];
		}
	}

	printf("Soma da linha 4: %d\n", soma_l4);
	printf("Soma da coluna 2: %d\n", soma_c2);
	printf("Soma da diagonal principal: %d\n", soma_dp);
	printf("Soma da diagonal secundaria: %d\n", soma_ds);
	printf("Soma total: %d\n", soma_t);



}