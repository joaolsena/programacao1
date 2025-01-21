#include <stdio.h>

int main() {
    int x = 10;
    int *ptr = &x; // Ponteiro que armazena o endereço de x

    printf("conteudo de x: %d\n", x);
    printf("Endereço de x: %p\n", &x);
    printf("conteudo apontado por ptr: %d\n", *ptr);
    printf("endereço apontado por ptr: %p\n", ptr);
    printf("endereco do ptr: %p\n", &ptr);

    x= x+10;
     printf("conteudo de x: %d\n", x);
     printf("Endereço de x: %p\n", &x);

    return 0;
}




