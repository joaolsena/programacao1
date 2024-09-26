#include <stdio.h>

int soma(int n1, int n2){
    int resultado = n1 + n2;

    return resultado;
}
int subtracao(int n1, int n2){
    int resultado = n1 - n2;

    return resultado;
}
float multiplicacao(int n1, int n2){
    float resultado = n1 * n2;

    return resultado;
}
float divisao(int n1, int n2){
    float resultado = n1 / n2;

    return resultado;
}


int main(){
float n1, n2;
char operacao;

    printf("\n");
    scanf("%f %c %f", &n1, &operacao, &n2);

    switch (operacao)
    {
        case '+':
            printf("%d", soma(n1, n2));
            break;
        case '-':
            printf("%d", subtracao(n1, n2));
            break;
        case '*':
            printf("%.2f", multiplicacao(n1, n2));
            break;
        case '/':
            if (n2 == 0){
                printf("Divisão por 0 não é permitida");
            }else
            printf("%.2f", divisao(n1, n2));
            break;
    }

    return 0;
}

//calculadora utilizando funçoes