#include <stdio.h>
#include <stdlib.h>

void func1 (int x) {
   x = 9 * x;
    printf("conteudo de x: %d\n", x);
    printf("Endereço de x: %p\n", &x);
}


//void func1 (int *x) {
   //*x = 9 * (*x);
//}


void func2 (int v[]) {
   v[0] = 9 * v[0];
}

int main (void) {
   int x, v[2];
   x    = 111; 
   func1 (x); printf ("x: %d\n", x);  printf("conteudo de x: %d\n", x);
    printf("Endereço de x: %p\n", &x);
//
   v[0] = 111; 
   func2 (v); printf ("v[0]: %d\n", v[0]);
   return EXIT_SUCCESS;
}
