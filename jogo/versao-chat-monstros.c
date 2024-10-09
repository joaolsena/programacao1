//tbm deu errado
#include <stdio.h>
#include <stdlib.h>

// Configurações de tela
#define MAX_tela_X 35
#define MAX_tela_y 25
#define MAX_margem 30

// Configurações de jogo
#define max_tiros 15
#define MAX_monstro 5 // Máximo de monstros por linha
#define MONSTRO_LARGURA 3 // Largura dos monstros
#define MONSTRO_ALTURA 2 // Altura dos monstros

int ponto = 0;
int vida = 3;
int direcao = 1;
int tempo_monstro = 0;
int velocidade = 1;
int posicao = MAX_tela_X / 10; // Posição inicial dos monstros
char imagem[MAX_tela_y][MAX_tela_X] = {0};

// Definições das formas dos monstros
const char monstro1_forma[MONSTRO_ALTURA][MONSTRO_LARGURA] = {
    {'/', '_', '\\'},
    {'|', ' ', '|'}
};

const char monstro2_forma[MONSTRO_ALTURA][MONSTRO_LARGURA] = {
    {'[', 'O', ']'},
    {'-', '-', '-'}
};

const char monstro3_forma[MONSTRO_ALTURA][MONSTRO_LARGURA] = {
    {'(', '^', ')'},
    {'/', ' ', '\\'}
};

// Estruturas para tiros, monstros e jogador
typedef struct {
    int ativo;
    int x;
    int y;
} tiros;

tiros tiro[max_tiros] = {{0, 0, 0}};

typedef struct {
    int ativo;
    int x;
    int y;
    const char (*forma)[MONSTRO_LARGURA]; // Ponteiro para a matriz de forma do monstro
} bicho;

bicho monstro[MAX_monstro * 2] = {{0, 0, 0, NULL}};
bicho monstro2[MAX_monstro * 2] = {{0, 0, 0, NULL}};
bicho monstro3[MAX_monstro] = {{0, 0, 0, NULL}};

typedef struct {
    int x;
    int y;
} jogado;

jogado jogador_p;

// Função para limpar a tela
void limpar() {
    system("clear"); // Usar "cls" no Windows
}

// Função para desenhar a tela
void tela() {
    printf("%*sPontos: %d", MAX_margem + 15, " ", ponto);
    printf("%*sVida: %d\n", MAX_margem + 15, "", vida);
    
    for (int i = 0; i < MAX_tela_y; i++) {
        for (int k = 0; k < MAX_margem; k++) {
            printf("  ");
        }
        for (int j = 0; j < MAX_tela_X; j++) {
            printf("%c", imagem[i][j]);
        }
        putchar('\n');
    }
}

// Função para inicializar o jogador
void jogador() {
    jogador_p.x = MAX_tela_X / 2;
    jogador_p.y = MAX_tela_y - 2;
    imagem[jogador_p.y][jogador_p.x] = '^';
}

// Função para desenhar um monstro na tela com base em uma matriz de forma
void desenha_monstro(bicho *monstro) {
    if (monstro->ativo) {
        for (int i = 0; i < MONSTRO_ALTURA; i++) {
            for (int j = 0; j < MONSTRO_LARGURA; j++) {
                imagem[monstro->y + i][monstro->x + j] = monstro->forma[i][j];
            }
        }
    }
}

// Função para inicializar monstros
void inicia_monstros() {
    for (int i = 0; i < MAX_monstro; i++) {
        monstro[i].ativo = 1;
        monstro[i].x = posicao + (MONSTRO_LARGURA * i);
        monstro[i].y = MAX_tela_y / 2;
        monstro[i].forma = monstro1_forma;
        desenha_monstro(&monstro[i]);

        monstro[i + MAX_monstro].ativo = 1;
        monstro[i + MAX_monstro].x = posicao + (MONSTRO_LARGURA * i);
        monstro[i + MAX_monstro].y = (MAX_tela_y / 2) - 3;
        monstro[i + MAX_monstro].forma = monstro2_forma;
        desenha_monstro(&monstro[i + MAX_monstro]);

        monstro3[i].ativo = 1;
        monstro3[i].x = posicao + (MONSTRO_LARGURA * i);
        monstro3[i].y = (MAX_tela_y / 2) - 6;
        monstro3[i].forma = monstro3_forma;
        desenha_monstro(&monstro3[i]);
    }
}

// Função para disparar tiros
void disparos() {
    for (int i = 0; i < max_tiros; i++) {
        if (!tiro[i].ativo) {
            tiro[i].ativo = 1;
            tiro[i].x = jogador_p.x;
            tiro[i].y = jogador_p.y - 1;  // O tiro começa acima do jogador
            imagem[tiro[i].y][tiro[i].x] = '|';
            break;
        }
    }
}

// Função para mover os tiros e verificar colisão com monstros
void mover_tiro() {
    for (int i = 0; i < max_tiros; i++) {
        if (tiro[i].ativo) {
            imagem[tiro[i].y][tiro[i].x] = ' '; // Apaga a posição anterior do tiro

            if (tiro[i].y > 0) {
                tiro[i].y--; // Move o tiro para cima
                imagem[tiro[i].y][tiro[i].x] = '|'; // Desenha o tiro na nova posição

                // Verifica colisão com monstros
                for (int j = 0; j < MAX_monstro * 2; j++) {
                    if (monstro[j].ativo) {
                        // Verifica se o tiro colide com o monstro considerando a largura e altura do monstro
                        if (tiro[i].x >= monstro[j].x && tiro[i].x < monstro[j].x + MONSTRO_LARGURA &&
                            tiro[i].y >= monstro[j].y && tiro[i].y < monstro[j].y + MONSTRO_ALTURA) {
                            // Colisão com monstro
                            ponto += 10;
                            monstro[j].ativo = 0;
                            tiro[i].ativo = 0;
                            // Apaga o monstro e o tiro da tela
                            for (int m = 0; m < MONSTRO_ALTURA; m++) {
                                for (int n = 0; n < MONSTRO_LARGURA; n++) {
                                    imagem[monstro[j].y + m][monstro[j].x + n] = ' ';
                                }
                            }
                            break;
                        }
                    }
                }
            } else {
                tiro[i].ativo = 0; // Desativa o tiro se ele sai da tela
            }
        }
    }
}

// Função para mover o jogador e processar disparos
void mover() {
    imagem[jogador_p.y][jogador_p.x] = ' ';
    char move;
    scanf("%c", &move);

    if (move == 'a' && jogador_p.x > 1) {
        jogador_p.x--;
    } else if (move == 'd' && jogador_p.x < MAX_tela_X - 2) {
        jogador_p.x++;
    } else if (move == ' ') {
        disparos(); // Dispara tiro
    } else if (move == 'q') {
        exit(0);
    }

    imagem[jogador_p.y][jogador_p.x] = '^';
}

// Função principal do jogo
int main() {
    jogador();
    inicia_monstros();
    while (1) {
        limpar();
        tela();
        mover();
        mover_tiro(); // Atualiza a posição dos tiros e verifica colisões
        // movimento_monstro(); // Você pode adicionar essa função para mover os monstros
    }
    return 0;
}
