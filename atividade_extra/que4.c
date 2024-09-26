#include <stdio.h>
#include <math.h>
//problema do cavalo.

int main() {
    char coluna_inicial, coluna_final;
    int linha_inicial, linha_final;

    
    scanf(" %c%d %c%d", &coluna_inicial, &linha_inicial, &coluna_final, &linha_final);

 
    int dx = abs(coluna_final - coluna_inicial);
    int dy = abs(linha_final - linha_inicial);

    if ((dx == 2 && dy == 1) || (dx == 1 && dy == 2)) {
        printf("VALIDO\n");
    } else {
        printf("INVALIDO\n");
    }

    return 0;
}
