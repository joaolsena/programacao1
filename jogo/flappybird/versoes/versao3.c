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
#define forma_obstaculo '@'

#define gravidade 1
#define pulo -2
#define espaco 3
#define ATRASO_TIQUE 200000
#define max_tubos 2

int ponto=0;

char imagem[MAX_tela_y][MAX_tela_X] = {0};

typedef struct {
    int x;
    int y;
} passaro;

passaro bird;

typedef struct {
    int x;
    int y;
} obstaculo;

obstaculo obstaculos[2];  // Dois obstáculos (pares de tubos)

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
    printf("%*sPontos: %d\n", MAX_margem + 45, "", ponto);
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
                printf("\033[33m%c\033[0m", forma_jogador);
            } else if (imagem[i][j] == forma_obstaculo) {
                printf("\033[32m%c\033[0m", forma_obstaculo);
            } else {
                printf(" ");
            }
        }
        putchar('\n');
    }
}

void inicia_jogador() {
    bird.x = 3;
    bird.y = (MAX_tela_y / 2) -4;
    imagem[bird.y][bird.x] = forma_jogador;
}

void inicia_obstaculos() {
    for (int i = 0; i < 2; i++) {
        obstaculos[i].x = MAX_tela_X - 1 - (i * (MAX_tela_X / 2));  
        obstaculos[i].y = (MAX_tela_y / 2) - (espaco / 2) + (rand() % 4);  
    }
}

void desenha_obstaculos() {
    for (int i = 0; i < max_tubos; i++) {
        for (int y = 0; y < MAX_tela_y; y++) {
            if (y < obstaculos[i].y || y > obstaculos[i].y + espaco) {
                if (obstaculos[i].x >= 0 && obstaculos[i].x < MAX_tela_X) {
                    imagem[y][obstaculos[i].x] = forma_obstaculo;
                    if (obstaculos[i].x + 1 < MAX_tela_X) {
                        imagem[y][obstaculos[i].x + 1] = forma_obstaculo;
                    }
                }
            }
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
    if (bird.y < 0) {
    bird.y = 0;
} else if (bird.y >= MAX_tela_y - 1) {
    bird.y = MAX_tela_y - 1;
}


    imagem[bird.y][bird.x] = forma_jogador;
}

void atualiza_obstaculos() {
    for (int i = 0; i < max_tubos; i++) {
        for (int y = 0; y < MAX_tela_y; y++) {
            if (obstaculos[i].x >= 0 && obstaculos[i].x < MAX_tela_X) {
                imagem[y][obstaculos[i].x] = ' ';
                if (obstaculos[i].x + 1 < MAX_tela_X) {
                    imagem[y][obstaculos[i].x + 1] = ' ';
                }
            }
        }

        obstaculos[i].x -= 1;

        if (obstaculos[i].x == bird.x - 1) {
            ponto += 10;
        }

        if (obstaculos[i].x < 1) {
            obstaculos[i].x = MAX_tela_X - 1;
            obstaculos[i].y = (MAX_tela_y / 2) - (espaco / 2) + (rand() % 4);  
        }
    }

    desenha_obstaculos();
}
void colisao() {
    for (int i = 0; i < max_tubos; i++) {
        if ((bird.x == obstaculos[i].x || bird.x == obstaculos[i].x + 1) && (bird.y < obstaculos[i].y || bird.y > obstaculos[i].y + espaco)) {   
                exit(1);  
        }
    }

    if (bird.y >= MAX_tela_y - 1 || bird.y < 0) {
        exit(1); 
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
        atualiza_obstaculos();
        colisao();
        usleep(ATRASO_TIQUE);
    }

    return 0;
}
