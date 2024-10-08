// nao pegou kkkkkkkkkkkk. porém é uma boa idea, mas muito trampo
#include <stdio.h>
#include <stdlib.h>

// Configurações de tela
#define MAX_tela_X 35
#define MAX_tela_y 25
#define MAX_margem 30

// Configurações de jogo
#define forma_jogador '^'
#define forma_tiro '|'
#define max_tiros 15
#define MAX_monstro 11 // Máximo de monstros por linha

// Tipos de monstros
#define monstro_1 'M'
#define monstro_2 'A'
#define monstro_3 'w'

int ponto = 0;
int vida = 3;
int direcao = 1;
int tempo_monstro = 0;
int velocidade = 1;
int posicao = MAX_tela_X / 10; // Posição inicial dos monstros
char imagem[MAX_tela_y][MAX_tela_X] = {0};

// Estrutura para tiros
typedef struct {
    int ativo;
    int x;
    int y;
} tiros;

tiros tiro[max_tiros] = {{0, 0, 0}};

// Estrutura para monstros, agora com um identificador de tipo
typedef struct {
    int ativo;
    int x;
    int y;
    char tipo; // Identificador de tipo: monstro_1, monstro_2, ou monstro_3
} monstro_t;

// Unificação das estruturas de monstros
monstro_t monstros[MAX_monstro * 5] = {{0, 0, 0, monstro_1}}; 

// Estrutura para o jogador
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
            if (i == MAX_tela_y - 1) {
                printf("_");
            } else if (imagem[i][j] == forma_jogador) {
                printf("%c", forma_jogador);
            } else if (imagem[i][j] == monstro_1 || imagem[i][j] == monstro_2 || imagem[i][j] == monstro_3) {
                printf("%c", imagem[i][j]);
            } else if (imagem[i][j] == forma_tiro) {
                printf("%c", forma_tiro);
            } else {
                printf(" ");
            }
        }
        putchar('\n');
    }
}

// Função para inicializar o jogador
void jogador() {
    jogador_p.x = MAX_tela_X / 2;
    jogador_p.y = MAX_tela_y - 2;
    imagem[jogador_p.y][jogador_p.x] = forma_jogador;
}

// Função para inicializar monstros
void inicia_monstros() {
    int total_monstros = 0;
    for (int i = 0; i < MAX_monstro; i++) {
        // Linha 1 de monstros (tipo 1)
        monstros[total_monstros].ativo = 1;
        monstros[total_monstros].x = posicao + (2 * i);
        monstros[total_monstros].y = MAX_tela_y / 2;
        monstros[total_monstros].tipo = monstro_1;
        imagem[monstros[total_monstros].y][monstros[total_monstros].x] = monstro_1;
        total_monstros++;

        // Linha 2 de monstros (tipo 1)
        monstros[total_monstros].ativo = 1;
        monstros[total_monstros].x = posicao + (2 * i);
        monstros[total_monstros].y = (MAX_tela_y / 2) - 1;
        monstros[total_monstros].tipo = monstro_1;
        imagem[monstros[total_monstros].y][monstros[total_monstros].x] = monstro_1;
        total_monstros++;

        // Linha 3 de monstros (tipo 2)
        monstros[total_monstros].ativo = 1;
        monstros[total_monstros].x = posicao + (2 * i);
        monstros[total_monstros].y = (MAX_tela_y / 2) - 2;
        monstros[total_monstros].tipo = monstro_2;
        imagem[monstros[total_monstros].y][monstros[total_monstros].x] = monstro_2;
        total_monstros++;

        // Linha 4 de monstros (tipo 2)
        monstros[total_monstros].ativo = 1;
        monstros[total_monstros].x = posicao + (2 * i);
        monstros[total_monstros].y = (MAX_tela_y / 2) - 3;
        monstros[total_monstros].tipo = monstro_2;
        imagem[monstros[total_monstros].y][monstros[total_monstros].x] = monstro_2;
        total_monstros++;

        // Linha 5 de monstros (tipo 3)
        monstros[total_monstros].ativo = 1;
        monstros[total_monstros].x = posicao + (2 * i);
        monstros[total_monstros].y = (MAX_tela_y / 2) - 4;
        monstros[total_monstros].tipo = monstro_3;
        imagem[monstros[total_monstros].y][monstros[total_monstros].x] = monstro_3;
        total_monstros++;
    }
}

// Função para disparar tiros
void disparos() {
    for (int i = 0; i < max_tiros; i++) {
        if (!tiro[i].ativo) {
            tiro[i].ativo = 1;
            tiro[i].x = jogador_p.x;
            tiro[i].y = jogador_p.y;
            imagem[tiro[i].y][tiro[i].x] = forma_tiro;
            break;
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
        disparos();
    } else if (move == 'q') {
        exit(0);
    }

    imagem[jogador_p.y][jogador_p.x] = forma_jogador;
}

// Função para verificar colisão entre tiros e monstros
void verificar_colisao() {
    for (int i = 0; i < max_tiros; i++) {
        if (tiro[i].ativo) {
            for (int j = 0; j < MAX_monstro * 5; j++) {
                if (monstros[j].ativo && tiro[i].x == monstros[j].x && tiro[i].y == monstros[j].y) {
                    // Adiciona pontos de acordo com o tipo de monstro
                    if (monstros[j].tipo == monstro_1) ponto += 10;
                    if (monstros[j].tipo == monstro_2) ponto += 20;
                    if (monstros[j].tipo == monstro_3) ponto += 40;

                    // Desativa o monstro e o tiro
                    monstros[j].ativo = 0;
                    imagem[monstros[j].y][monstros[j].x] = ' ';
                    tiro[i].ativo = 0;
                    break;
                }
            }
        }
    }
}

// Função para mover tiros
void mover_tiro() {
    for (int i = 0; i < max_tiros; i++) {
        if (tiro[i].ativo) {
            imagem[tiro[i].y][tiro[i].x] = ' ';

            if (tiro[i].y > 0) {
                tiro[i].y--;
                imagem[tiro[i].y][tiro[i].x] = forma_tiro;
            } else {
                tiro[i].ativo = 0;
            }
        }
    }
    verificar_colisao();
}

// Função para mover monstros
void movimento_monstro() {
    for (int i = 0; i < MAX_monstro * 5; i++) {
        if (monstros[i].ativo) {
            imagem[monstros[i].y][monstros[i].x] = ' ';
            monstros[i].x += direcao;

            // Se chegar ao limite, descer uma linha e mudar direção
            if (monstros[i].x >= MAX_tela_X - 2 || monstros[i].x <= 1) {
                direcao = -direcao;
                monstros[i].y++;
            }

            imagem[monstros[i].y][monstros[i].x] = monstros[i].tipo;

            // Verifica se algum monstro alcançou a posição do jogador
            if (monstros[i].y == jogador_p.y) {
                vida--;
                if (vida == 0) {
                    printf("Game Over! Você perdeu todas as vidas.\n");
                    exit(0);
                }
            }
        }
    }
}

int main() {
    jogador();
    inicia_monstros();
    while (1) {
        limpar();
        tela();
        mover();
        mover_tiro();
        movimento_monstro();
    }
    return 0;
}
