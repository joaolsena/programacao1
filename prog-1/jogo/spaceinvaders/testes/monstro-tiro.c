#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Configurações de tela
#define MAX_tela_X 50
#define MAX_tela_y 20
#define MAX_margem 30

/// Configurações de jogo
#define forma_jogador '^'
#define forma_tiro '|'
#define forma_tiro_monstro '!'
#define max_tiros 20
#define monstro_1 'M'
#define monstro_2 'H'
#define monstro_3 'W'
#define MAX_monstro 10 // Máximo de monstros por linha
#define max_tiro_monstro 10


// Variáveis globais
int ponto = 0;
int vida = 3;
int direcao = 1;
int tempo_monstro = 0;
int velocidade = 1;
int velocidade1=0;
int tempo_tiro_monstro = 0;
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
} tiros_monstros;

tiros_monstros tiro_monstros[max_tiro_monstro] = {{0, 0, 0}};

typedef struct {
    int ativo;
    int x;
    int y;
} bicho;
bicho monstro[MAX_monstro * 2] = {{0, 0, 0}}; // Monstros superior e inferior

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
    printf("%*svida: %d\n", MAX_margem + 15, "", vida);
    
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
            }else if (imagem[i][j] == forma_tiro_monstro){
                 printf("\033[31m%c\033[0m", forma_tiro_monstro);}
             else if (imagem[i][j] == forma_tiro) {
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
    // Inicializar monstros inferiores
    for (int i = 0; i < MAX_monstro; i++) {
        monstro[i].ativo = 1;
        monstro[i].x = posicao + (2 * i);
        monstro[i].y = MAX_tela_y / 2;
        imagem[monstro[i].y][monstro[i].x] = monstro_1;
    }
    // Inicializar monstros superiores
    for (int i = MAX_monstro; i < MAX_monstro * 2; i++) {
        monstro[i].ativo = 1;
        monstro[i].x = posicao + (2 * (i - MAX_monstro));
        monstro[i].y = (MAX_tela_y / 2) - 1;
        imagem[monstro[i].y][monstro[i].x] = monstro_1;
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

            for (int j = 0; j < MAX_monstro * 2; j++) {
                if (monstro[j].ativo && tiro[i].x == monstro[j].x && tiro[i].y == monstro[j].y) {
                    ponto += 10;
                    monstro[j].ativo = 0;
                    imagem[monstro[j].y][monstro[j].x] = ' ';
                    tiro[i].ativo = 0;
                    break;
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

        // Move os monstros para a nova posição
        for (int i = 0; i < MAX_monstro * 2; i++) {
            if (monstro[i].ativo) {
                monstro[i].x += direcao;
            }
        }

        // Verifica colisão com borda e ajusta direcao
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
                velocidade++;
                break;
            }
        }

        // Atualiza as novas posições dos monstros
        for (int i = 0; i < MAX_monstro * 2; i++) {
            if (monstro[i].ativo) {
                imagem[monstro[i].y][monstro[i].x] = monstro_1;
            }
        }
    }
}
void tiro_monster() {
    for (int i = 0; i < max_tiro_monstro; i++) {
        if (!tiro_monstros[i].ativo) {
            // Seleciona aleatoriamente um monstro para disparar
            int chance_tiro = rand() % 2;
            int monstro_atirador = rand() % (MAX_monstro * 2);

            if (chance_tiro == 0 && monstro[monstro_atirador].ativo && monstro_atirador > MAX_monstro) {
                tiro_monstros[i].ativo = 1;
                tiro_monstros[i].x = monstro[monstro_atirador].x;
                tiro_monstros[i].y = monstro[monstro_atirador].y + 1;
            }
        } else {
            tempo_tiro_monstro++;

            if (tempo_tiro_monstro > 0) {
                tempo_tiro_monstro = 0;

                // Remove o rastro do tiro anterior, se não houver um monstro nessa posição
                if (imagem[tiro_monstros[i].y][tiro_monstros[i].x] == forma_tiro_monstro) {
                    imagem[tiro_monstros[i].y][tiro_monstros[i].x] = ' ';
                }

                // Verifica se a próxima posição do tiro está ocupada por outro monstro
                if (tiro_monstros[i].y < MAX_tela_y - 1) {
                    int proxima_y = tiro_monstros[i].y + 1;

                    // Checa se a posição abaixo do tiro tem um monstro
                    int monstro_na_proxima_posicao = 0;
                    for (int j = 0; j < MAX_monstro * 2; j++) {
                        if (monstro[j].ativo && monstro[j].x == tiro_monstros[i].x && monstro[j].y == proxima_y) {
                            monstro_na_proxima_posicao = 1;
                            break;
                        }
                    }

                    if (!monstro_na_proxima_posicao) {
                        tiro_monstros[i].y++; // Move o tiro para a próxima posição
                        imagem[tiro_monstros[i].y][tiro_monstros[i].x] = forma_tiro_monstro;
                    } else {
                        tiro_monstros[i].ativo = 0; // Desativa o tiro se ele não pode continuar
                    }
                } else {
                    tiro_monstros[i].ativo = 0; // Desativa o tiro ao chegar no limite inferior
                }
            }

            // Verifica se o tiro do monstro atingiu o jogador
            if (tiro_monstros[i].ativo && tiro_monstros[i].x == jogador_p.x && tiro_monstros[i].y == jogador_p.y) {
                vida--;
                tiro_monstros[i].ativo = 0;
                imagem[tiro_monstros[i].y][tiro_monstros[i].x] = ' ';
                if (vida == 0) {
                    printf("\nGame Over!\n");
                    exit(0);
                }
            }
        }
    }
}


// Função principal do jogo
int main() {
    srand(time(NULL));
    jogador();
    inicia_monstros();
    while (1) {
        limpar();
        tela();
        mover();
        mover_tiro();
        movimento_monstro();
        tiro_monster();
    }
    return 0;
}
