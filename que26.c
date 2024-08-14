#include <stdio.h>

int main() {
    int p,a, aa;
    printf("selecione um tipo de evento:\n1 para Concerto\n2 para Teatro\n3 para Evento Esportivo\n4 para Conferência\n");
    scanf("%d", &p);
    printf("quantos assentos voce deseja resevar\n");
    scanf("%d", &a);
    switch (p)
    {
    case 1:
           aa=500;
           if (a<=500) {
            printf("reserva confirmada! voce reservou %d\nrestou %d de assentos\n", a,aa-a);
           } else {
            printf("não há assentos suficientes disponíveis");
           }
        break;
        case 2:
        aa=200;
           if (a<=200) {
            printf("reserva confirmada! voce reservou %d\nrestou %d de assentos\n",a,aa-a);
           } else {
            printf("não há assentos suficientes disponíveis");
           }
           break;
           case 3:
           aa=1000;
           if (a<=1000) {
            printf("reserva confirmada! voce reservou %d\nrestou %d de assentos\n",a,aa-a);
           } else {
            printf("não há assentos suficientes disponíveis");
           }
           break;
           case 4:
           aa=300;
           if (a<=300) {
            printf("reserva confirmada! voce reservou %d\nrestou %d de assentos\n",a,aa-a);
           } else {
            printf("não há assentos suficientes disponíveis");
           }
           break;
    default:
    printf("numero inserido invalido\n");
        break;
    }
    return 0;
}
