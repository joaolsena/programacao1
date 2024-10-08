#include <stdio.h>
#include <stdlib.h>
#include <windows.h>  // Biblioteca para manipular o console
#include <conio.h>  // biblioteca conio.h para usar getch()

#define MAX_tela_X 30
#define MAX_tela_y 20
#define forma_jogador '^'
#define forma_tiro '|'
#define max_tiros 5
#define monstro_1 'M'
#define MAX_monstro 15 // máximo de monstros por linha

// a para a esquerda. d para a direita. espaço para atirar. q para sair.

int ponto = 0;
int posicao = MAX_tela_X - 2; // posiciona cada monstro um do lado do outro
char imagem[MAX_tela_y][MAX_tela_X] = {0};

typedef struct {
    int ativo;
    int x;
    int y;
} tiros;

tiros tiro[max_tiros] = {{0,0,0}};

typedef struct {
    int ativo;
    int x;
    int y;
} bicho;

bicho monstro[MAX_monstro] = {{0,0,0}};

typedef struct {
    int x;
    int y;
} jogado;

jogado jogador_p;

// Função para mover o cursor para a posição desejada
void setCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Função para esconder o cursor
void hideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = FALSE;
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void tela() {
    // Move o cursor para o topo e sobrescreve a tela sem limpá-la
    setCursorPosition(0, 0);
    
    printf("Pontos: %d\n", ponto);
    
    for (int i = 0; i < MAX_tela_y; i++) {
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
        monstro[i].x = posicao--;
        monstro[i].y = MAX_tela_y / 2;
        imagem[monstro[i].y][monstro[i].x] = monstro_1;
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
    
    // Usa getch para ler a tecla pressionada sem Enter
    if (_kbhit()) {
        char move = getch();
        
        if (move == 'a' && jogador_p.x > 1) {
            jogador_p.x--;
        } else if (move == 'd' && jogador_p.x < MAX_tela_X - 2) {
            jogador_p.x++;
        } else if (move == ' ') {
            disparos();
        } else if (move == 'q') {
            exit(0);
        }
    }
    
    imagem[jogador_p.y][jogador_p.x] = forma_jogador;
}

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

            for (int j = 0; j < MAX_monstro; j++) {
                if (monstro[j].ativo && tiro[i].x == monstro[j].x && tiro[i].y == monstro[j].y) {
                    ponto += 10;
                    monstro[j].ativo = 0;
                    imagem[monstro[j].y][monstro[j].x] = ' ';
                }
            }
        }
    }
}

int main() {
    // Inicializa o jogo
    jogador();
    inicia_monstros();
    
    // Esconde o cursor do console
    hideCursor();
    
    while (1) {
        // Atualiza a tela sem flickering
        tela();
        mover();
        mover_tiro();
        
        // Pausa para dar tempo entre os frames
        Sleep(50);  // 50ms de delay para suavizar os movimentos
    }
    
    return 0;
}
