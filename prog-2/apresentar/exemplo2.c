#include <stdio.h>
#include <stdlib.h> // Para malloc

int main() {
    int *p; // Inicializa o ponteiro com NULL
    
  
    if (p == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    // Usa o ponteiro com segurança
    printf("Valor armazenado: %d\n", *p);
	printf("endereco: %p\n", p);

    return 0;
}
