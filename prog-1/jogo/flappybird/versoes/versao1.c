#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>

#define MAX_tela_X 40
#define MAX_tela_y 20
#define MAX_margem 30

#define forma_jogador '>'
#define forma_obstacluo '@'

#define gravidade 1
#define pulo -2
#define espaco 2

#define ATRASO_TIQUE 200000

char imagem[MAX_tela_y][MAX_tela_X] = {0};

typedef struct {
    int x;
    int y;
} passaro;

passaro bird;

typedef struct {
    int x;
    int y;
} obstacluos;

obstacluos obstacluo;

int kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

int getch(void) {
    struct termios oldt, newt;
    int move;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    move = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return move;
}

void limpar() {
    system("clear");
}

void tela() {
    for (int i = 0; i < MAX_tela_y; i++) {
        for (int k = 0; k < MAX_margem; k++) {
            printf("  ");
        }
        for (int j = 0; j < MAX_tela_X; j++) {
            if (i == 0) {
                printf("\033[37m_\033[0m");
            } else if (j == 0 || j == MAX_tela_X - 1) {
                printf("|");
            } else if (i == MAX_tela_y - 1) {
                printf("-");
            } else if (imagem[i][j] == forma_jogador) {
                printf("\033[34m%c\033[0m", forma_jogador);
            } else if (imagem[i][j] == forma_obstacluo) {
                printf("%c", forma_obstacluo);
            } else {
                printf(" ");
            }
        }
        putchar('\n');
    }
}

void inicia_jogador() {
    bird.x = 3;
    bird.y = MAX_tela_y / 2;
    imagem[bird.y][bird.x] = forma_jogador;
}

void inicia_obstaculos() {
    obstacluo.x = MAX_tela_X - 1;
    obstacluo.y = rand() % (MAX_tela_y - espaco);
    for (int i = 0; i < MAX_tela_y; i++) {
        if (i < obstacluo.y || i > obstacluo.y + espaco) {
            imagem[i][obstacluo.x] = forma_obstacluo;
        }
    }
}

void atualiza_jogador() {
    imagem[bird.y][bird.x] = ' ';
    
    if (kbhit() && getch() == ' ') {
        bird.y += pulo;
    } else {
        bird.y += gravidade;
    }
    
    if (bird.y < 1) bird.y = 1;
    if (bird.y >= MAX_tela_y - 1) bird.y = MAX_tela_y - 2;

    imagem[bird.y][bird.x] = forma_jogador;
}

void atualiza_obstaculo() {
    for (int i = 0; i < MAX_tela_y; i++) {
        imagem[i][obstacluo.x] = ' ';
    }
    
    obstacluo.x -= 1;

    if (obstacluo.x < 1) {
        obstacluo.x = MAX_tela_X - 1;
        obstacluo.y = rand() % (MAX_tela_y - espaco);
    }

    for (int i = 0; i < MAX_tela_y; i++) {
        if (i < obstacluo.y || i > obstacluo.y + espaco) {
            imagem[i][obstacluo.x] = forma_obstacluo;
        }
    }
}

int main() {
    srand(time(NULL));
    inicia_jogador();
    inicia_obstaculos();

    while (1) {
        limpar();
        tela();

        atualiza_jogador();
        atualiza_obstaculo();

        usleep(ATRASO_TIQUE);
    }

    return 0;
}
