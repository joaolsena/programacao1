#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int escolhaJogador;
    int escolhaComputador;
    // 1 = Pedra, 2 = Papel, 3 = Tesoura

    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    // Solicita a escolha do jogador
    printf("Escolha:\n");
    printf("1 - Pedra\n");
    printf("2 - Papel\n");
    printf("3 - Tesoura\n");
    printf("Digite sua escolha (1, 2 ou 3): ");
    scanf("%d", &escolhaJogador);

    // Gera a escolha do computador
    escolhaComputador = rand() % 3 + 1;

    // Exibe a escolha do computador
    printf("Escolha do computador: ");
    switch (escolhaComputador) {
        case 1:
            printf("Pedra\n");
            break;
        case 2:
            printf("Papel\n");
            break;
        case 3:
            printf("Tesoura\n");
            break;
    }

    // Determina o resultado
    if (escolhaJogador == escolhaComputador) {
        printf("Empate!\n");
    } else if ((escolhaJogador == 1 && escolhaComputador == 3) || // Pedra ganha de Tesoura
               (escolhaJogador == 2 && escolhaComputador == 1) || // Papel ganha de Pedra
               (escolhaJogador == 3 && escolhaComputador == 2)) { // Tesoura ganha de Papel
        printf("Vitória!\n");
    } else {
        printf("Derrota!\n");
    }

    return 0;
}
