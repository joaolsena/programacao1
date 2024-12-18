#include <stdio.h>
int main() {
    int v;
    printf("insira o volume em litros da caixa cujo volume maximo é 100l\n");
    scanf("%d", &v);
    if (v<=10) {
        printf("baixo nivel de agua\n");
    } else if (v>10 && v<=50) {
        printf("nivel de agua medio\n");
    } else if (v>50 && v<100){
        printf("nivel de agua alto\n");
    } else if(v==100){
        printf("a caixa esta cheia\n");
    } else {
        printf("nem cabe isso\n");
    }
    return 0;
}