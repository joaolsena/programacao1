#include <stdio.h>
#include <stdlib.h>

// Configurações de tela
#define MAX_tela_X 50
#define MAX_tela_y 20
#define MAX_margem 30

// Configurações de jogo
#define forma_jogador '^'
#define forma_tiro '|'
#define max_tiros 5
#define monstro_1 'M'
#define monstro_2 'A'
#define MAX_monstro 15 // Máximo de monstros por linha

// Variáveis globais
int ponto = 0;
int vida = 3;
int direcao = 1;
int tempo_monstro = 0;
int velocidade = 1;
int teste = 0;
int posicao = MAX_tela_X / 10; // Posição inicial dos monstros
char imagem[MAX_tela_y][MAX_tela_X] = {0};

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
} bicho;

bicho monstro[MAX_monstro * 2] = {{0, 0, 0}}; // Monstros superior e inferior

typedef struct {
    int ativo;
    int x;
    int y;
} bicho2;

bicho2 monstro2[MAX_monstro*2] = {{0, 0, 0}}; // Monstros adicionais

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
            } else if (imagem[i][j] == monstro_1) {
                printf("%c", monstro_1);
            } else if (imagem[i][j] == monstro_2) {
                printf("%c", monstro_2);
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
    for (int i = 0; i < MAX_monstro; i++) {
        // Monstros inferiores
        monstro[i].ativo = 1;
        monstro[i].x = posicao + (2 * i);
        monstro[i].y = MAX_tela_y / 2;
        imagem[monstro[i].y][monstro[i].x] = monstro_1;

        // Monstros superiores
        monstro[i + MAX_monstro].ativo = 1;
        monstro[i + MAX_monstro].x = posicao + (2 * i);
        monstro[i + MAX_monstro].y = (MAX_tela_y / 2) - 1;
        imagem[monstro[i + MAX_monstro].y][monstro[i + MAX_monstro].x] = monstro_1;

        // Monstros adicionais
        monstro2[i].ativo = 1;
        monstro2[i].x = posicao + (2 * i);
        monstro2[i].y = (MAX_tela_y / 2) - 2;

        imagem[monstro2[i].y][monstro2[i].x] = monstro_2;
        monstro2[i].ativo = 1;
        monstro2[i].x = posicao + (2 * i);
        monstro2[i].y = (MAX_tela_y / 2) - 3;
        imagem[monstro2[i].y][monstro2[i].x] = monstro_2;
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
    scanf("%c", &move);  // Adiciona um espaço antes de %c para ignorar espaços em branco

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

// Função para mover os tiros e verificar colisão com monstros
void mover_tiro() {
    for (int i = 0; i < max_tiros; i++) {
        if (tiro[i].ativo) {
            imagem[tiro[i].y][tiro[i].x] = ' ';

            if (tiro[i].y > 1) {
                tiro[i].y--;
                imagem[tiro[i].y][tiro[i].x] = forma_tiro;
            } else {
                tiro[i].ativo = 0;
            }

            // Verifica colisão com monstros do tipo 1
            for (int j = 0; j < MAX_monstro * 2; j++) {
                if (monstro[j].ativo && tiro[i].x == monstro[j].x && tiro[i].y == monstro[j].y) {
                    ponto += 10; // Colisão com monstro 1
                    monstro[j].ativo = 0;
                    imagem[monstro[j].y][monstro[j].x] = ' ';
                    tiro[i].ativo = 0;
                    break; // Para não verificar mais após a colisão
                }
            }

            // Verifica colisão com monstros do tipo 2
            for (int j = 0; j < MAX_monstro*2; j++) {
                if (monstro2[j].ativo && tiro[i].x == monstro2[j].x && tiro[i].y == monstro2[j].y) {
                    ponto += 20; // Ganha 20 pontos ao colidir com monstro 2
                    monstro2[j].ativo = 0;
                    imagem[monstro2[j].y][monstro2[j].x] = ' ';
                    tiro[i].ativo = 0;
                    break; // Para não verificar mais após a colisão
                }
            }
        }
    }
}

// Função para mover monstros e atualizar suas posições
void movimento_monstro() {
    tempo_monstro++;
    if (tempo_monstro >= (4 - velocidade)) {
        tempo_monstro = 0;

        // Remove monstros das posições atuais
        for (int i = 0; i < MAX_monstro * 2; i++) {
            if (monstro[i].ativo) {
                imagem[monstro[i].y][monstro[i].x] = ' ';
            }
        }
        
        // Remove monstros adicionais das posições atuais
        for (int i = 0; i < MAX_monstro*2; i++) {
            if (monstro2[i].ativo) {
                imagem[monstro2[i].y][monstro2[i].x] = ' ';
            }
        }

        // Move os monstros do tipo 1 para a nova posição
        for (int i = 0; i < MAX_monstro * 2; i++) {
            if (monstro[i].ativo) {
                monstro[i].x += direcao;
            }
        }

        // Move os monstros do tipo 2 para a nova posição
        for (int i = 0; i < MAX_monstro*2; i++) {
            if (monstro2[i].ativo) {
                monstro2[i].x += direcao;
            }
        }

        // Verifica colisão com borda e ajusta direção
        for (int i = 0; i < MAX_monstro * 2; i++) {
            if (monstro[i].ativo && (monstro[i].x <= 0 || monstro[i].x >= MAX_tela_X - 1)) {
                direcao *= -1;

                for (int j = 0; j < MAX_monstro * 2; j++) {
                    if (monstro[j].ativo) {
                        monstro[j].y += 1;
                        if (monstro[j].y >= MAX_tela_y - 3) {
                            vida--;
                            if (vida == 0) {
                                printf("\nGame Over!\n");
                                exit(0);
                            }
                        }
                    }
                }

                // Move os monstros do tipo 2 para baixo também
                for (int j = 0; j < MAX_monstro*2; j++) {
                    if (monstro2[j].ativo) {
                        monstro2[j].y += 1;
                        if (monstro2[j].y >= MAX_tela_y - 3) {
                            vida--;
                            if (vida == 0) {
                                printf("\nGame Over!\n");
                                exit(0);
                            }
                        }
                    }
                }

                velocidade++;
                break;
            }
        }

        // Atualiza as novas posições dos monstros do tipo 1
        for (int i = 0; i < MAX_monstro * 2; i++) {
            if (monstro[i].ativo) {
                imagem[monstro[i].y][monstro[i].x] = monstro_1;
            }
        }

        // Atualiza as novas posições dos monstros do tipo 2
        for (int i = 0; i < MAX_monstro*2; i++) {
            if (monstro2[i].ativo) {
                imagem[monstro2[i].y][monstro2[i].x] = monstro_2;
            }
        }
    }
}

// Função principal do jogo
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
