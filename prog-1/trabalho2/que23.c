#include <stdio.h>

int main() {
    int horario, trafego;
    int tempoVerde, tempoAmarelo, tempoVermelho;

    
    printf("Informe o horário do dia (1 = manhã, 2 = tarde, 3 = noite): ");
    scanf("%d", &horario);

    
    printf("Informe o nível de tráfego (1 = baixo, 2 = médio, 3 = alto): ");
    scanf("%d", &trafego);

    
    tempoVerde = 30;    
    tempoAmarelo = 5;   
    tempoVermelho = 30; 
    switch(horario) {
        case 1: 
            if (trafego == 1) { 
                tempoVerde -= 10;  
                tempoVermelho += 10; 
            } else if (trafego == 3) { 
                tempoVerde += 10;  
                tempoVermelho -= 10; 
            }
            break;

        case 2: 
            if (trafego == 1) { 
                tempoVerde -= 5;  
                tempoVermelho += 5; 
            } else if (trafego == 3) { 
                tempoVerde += 5;  
                tempoVermelho -= 5; 
            }
            break;

        case 3: 
            if (trafego == 1) { 
                tempoVerde -= 15;  
                tempoVermelho += 15; 
            } else if (trafego == 3) { 
                tempoVerde += 15;  
                tempoVermelho -= 15; 
            }
            break;

        default:
            printf("Horário inválido.\n");
            return 1; 
    }

    
    printf("Tempos ajustados:\n");
    printf("Verde: %d segundos\n", tempoVerde);
    printf("Amarelo: %d segundos\n", tempoAmarelo);
    printf("Vermelho: %d segundos\n", tempoVermelho);

    return 0;
}
