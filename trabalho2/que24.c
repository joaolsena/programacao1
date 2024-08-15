#include <stdio.h> 
int main(){
    int c;
    float t;
    printf("insira o clima 1 para ensolarado, 2 para nublado, 3 para chuvoso\n");
    scanf("%d", &c);
     printf("insira a temperatura\n");
    scanf("%f", &t);
    switch (c)
    {
    case 1:
        if (t>20) {
            printf("sugiro que faça atividades ao ar livre como ir à praia ou fazer um piquenique\n");
        } else if (t>=15 && t<=25){
            printf("sugiro que faça caminhadas ou passeios de bicicleta\n");
        } else if (t<15){
             printf("sugiro que faça atividades como fotografia da natureza ou observação de pássaros\n");
        }
        break;
        case 2:
         if (t>20) {
            printf("sugiro que faça visitas em museus ou fazer compras em centros comerciais ao ar livre\n");
        } else if (t>=10 && t<=20){
            printf("sugiro que faça passeios culturais, como galerias de arte ou teatros\n");
        } else if (t<10){
             printf("sugiro que faça leitura em bibliotecas ou sessões de cinema\n");
        }
        break;
        case 3:
        if (t>15) {
            printf("sugiro que visite um spa ou faça aulas de culinária.\n");
        } else if (t>=5 && t<=15){
            printf("sugiro que visite museus de ciência ou sessões de boliche\n");
        } else if (t<5){
             printf("recomendo uma tarde de jogos de tabuleiro em casa ou uma maratona de filmes\n");
        }
        break;
    default:
    printf("codigo invalido\n");
        break;
    }
    return 0;
} 