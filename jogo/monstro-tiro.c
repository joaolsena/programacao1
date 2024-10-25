#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Para gerar números aleatórios

// tela
#define MAX_tela_X 50
#define MAX_tela_y 20
#define MAX_margem 30

// jogo
#define forma_jogador '^'
#define forma_tiro '|'
#define max_tiros 20
#define max_tiro_monstro 4
#define monstro_1 'M'
#define monstro_4 'x'
#define MAX_monstro 15 // máximo de monstro por linha

// a para a esquerda. d para a direita. espaço para atirar. q para sair.
int ponto = 0;
int vida = 3;
int posicao = MAX_tela_X / 10; // posiciona cada monstro um do lado do outro se encontra no void inicia monstro
char imagem[MAX_tela_y][MAX_tela_X] = {0};
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

bicho monstro[MAX_monstro] = {{0, 0, 0}};

typedef struct {
    int ativo;
    int x;
    int y;
} tiros_monstros;

tiros_monstros tiro_monstros[max_tiro_monstro] = {{0, 0, 0}};

typedef struct {
    int x;
    int y;
} jogado;

jogado jogador_p;

void limpar() {
    system("clear"); // Usar cls se estiver no Windows
}

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
            } else if (imagem[i][j] == forma_tiro) {
                printf("%c", forma_tiro);
            } else {
                printf(" ");
            }
        }
        putchar('\n');
    }
}


void jogador() {
    jogador_p.x = MAX_tela_X / 2;
    jogador_p.y = MAX_tela_y - 2;
    imagem[jogador_p.y][jogador_p.x] = forma_jogador;
}

void inicia_monstros() {
    for (int i = 0; i < MAX_monstro; i++) {
        monstro[i].ativo = 1;
        monstro[i].x = posicao + (2 * i);
        monstro[i].y = MAX_tela_y / 2;
        imagem[monstro[i].y][monstro[i].x] = monstro_1;

        monstro[i].ativo = 1;
        monstro[i].x = posicao + (2 * i);
        monstro[i].y = (MAX_tela_y / 2)+1;
        imagem[monstro[i].y][monstro[i].x] = monstro_1;
    }
}

int direcao = 1;
void movimento_monstro() {
    for (int i = 0; i < MAX_monstro * 2; i++) {
        if (monstro[i].ativo) {
            imagem[monstro[i].y][monstro[i].x] = ' ';
            monstro[i].x += direcao;
        }
    }

    for (int i = 0; i < MAX_monstro*2; i++) {
        if (monstro[i].ativo && (monstro[i].x >= MAX_tela_X - 1 || monstro[i].x <= 0)) {
            direcao *= -1;
        }
    }

    for (int i = 0; i < MAX_monstro*2; i++) {
        if (monstro[i].ativo) {
            imagem[monstro[i].y][monstro[i].x] = monstro_1;
        }
    }
         
    }
    


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

void mover() {
    imagem[jogador_p.y][jogador_p.x] = ' ';
    char move;
    scanf("%c", &move); 

    if (move == 'a' && jogador_p.x > 1) {
        jogador_p.x--;
    } else if (move == 'd' && jogador_p.x < MAX_tela_X - 2) {
        jogador_p.x++;
       
    } else if (move== ' ') {
        disparos();
    } else if (move == 'q') {
        exit(0);
    }

    imagem[jogador_p.y][jogador_p.x] = forma_jogador;
}

void mover_tiro() {
    for (int i = 0; i < max_tiros; i++) {
        if (tiro[i].ativo) {
            imagem[tiro[i].y][tiro[i].x] = ' ';

            if (tiro[i].y > -1) {
                tiro[i].y--;
                imagem[tiro[i].y][tiro[i].x] = forma_tiro;
            } else {
                tiro[i].ativo = 0;
            }

            for (int j = 0; j < MAX_monstro; j++) {
                if (monstro[j].ativo && tiro[i].x == monstro[j].x && tiro[i].y == monstro[j].y) {
                    ponto += 10;
                    monstro[j].ativo = 0;
                    imagem[monstro[j].y][monstro[j].x] = ' ';
                    tiro[i].ativo = 0;
                }
            }
                
        }
    }
}

void tiro_monster() {
    for (int i = 0; i < max_tiro_monstro; i++) {
        if (!tiro_monstros[i].ativo) {
            // Seleciona aleatoriamente um monstro para disparar
            int monstro_atirador = rand() % MAX_monstro;
            if (monstro[monstro_atirador].ativo) {
                tiro_monstros[i].ativo = 1;
                tiro_monstros[i].x = monstro[monstro_atirador].x;
                tiro_monstros[i].y = monstro[monstro_atirador].y + 1;
            }
        } else {
            // Movimento do tiro do monstro
            imagem[tiro_monstros[i].y][tiro_monstros[i].x] = ' ';
            if (tiro_monstros[i].y < MAX_tela_y - 1) {
                tiro_monstros[i].y++;
                imagem[tiro_monstros[i].y][tiro_monstros[i].x] = forma_tiro;
            } else {
                tiro_monstros[i].ativo = 0;
            }

            // Verifica se o tiro do monstro atingiu o jogador
            if (tiro_monstros[i].ativo && tiro_monstros[i].x == jogador_p.x && tiro_monstros[i].y == jogador_p.y) {
                vida--;
                tiro_monstros[i].ativo = 0;
                if (vida <= 0) {
                    printf("Game Over!\n");
                    exit(0);
                }
            }
        }
    }
}

int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios
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
