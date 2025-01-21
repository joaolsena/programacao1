#include <stdio.h>

void imprime(char *v, int n) {
   
   for (char *c = v; c < v + n; c++)
      printf("%c", *c);
}

int main() {
    char texto[20];
    int n;
    scanf("%c, %n", &texto,  &n);

    imprime(texto, n); // Imprime os primeiros 4 caracteres de "OpenAI"

    return 0;
}
