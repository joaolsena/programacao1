#include <stdio.h>
int main(){
    int p;
    printf("insira um numero de 1 a 7\n");
    scanf("%d", &p);
    switch (p)
    {
    case 1:
        printf("domingo\n");
        break;
        case 2:
        printf("segunda\n");
        break;
        case 3:
        printf("terça\n");
        break;
        case 4:
        printf("quarta\n");
        break;
        case 5:
        printf("quinta\n");
        break;
        case 6:
        printf("sexta\n");
        break;
        case 7:
        printf("sabado\n");
        break;
    default:
    printf("numero invalido\n");
        break;
    }
    return 0;
}