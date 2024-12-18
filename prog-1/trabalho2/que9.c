#include <stdio.h>
int main() {
    int n;

    printf("insira a nota do aluno entre 0 e 100\n");
    scanf("%d", &n);
    if (n>=80 && n<=100) {
        printf("excelente\n");
    } else if (n>=60 && n<80) {
        printf("bom\n");
    } else if (n>=40 && n<60) {
        printf("suficiente\n");
    } else if (n<40) {
        printf("insuficiente\n");
    } else {
        printf("nota invalida\n");
    }
    return 0;
}