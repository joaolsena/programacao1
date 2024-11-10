#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>

#define MAX_tela_X 50
#define MAX_tela_y 30
#define MAX_margem 30

#define forma_cabeca '0'
#define forma_corpo 'o'
#define forma_comida '@'

#define ATRASO_TIQUE 200000
#define MAX_CORPO 100  

int ponto = 0;
int tamanho_corpo = 0; 
int direcao_x = 1;  
int direcao_y = 0;

char imagem[MAX_tela_y][MAX_tela_X] = {0};

typedef struct {
    int x;
    int y;
} cabecas;

cabecas cabeca;

typedef struct {
    int x;
    int y;
} corpos;

corpos corpo[MAX_CORPO];

typedef struct {
    int x;
    int y;
    int ativo;
} comidas;

comidas comida;

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
            if (j == 0 || j == MAX_tela_X - 1 || i == MAX_tela_y - 1 || i == 0) {
                printf("\033[35m#\033[0m");
            } else if (imagem[i][j] == forma_cabeca) {
                printf("\033[32m%c\033[0m", forma_cabeca);
            } else if (imagem[i][j] == forma_corpo) {
                printf("\033[32m%c\033[0m", forma_corpo);
            } else if (imagem[i][j] == forma_comida) {
                printf("\033[31m%c\033[0m", forma_comida);
            } else {
                printf(" ");
            }
        }
        putchar('\n');
    }
}

void inicia_cobra() {
    cabeca.x = MAX_tela_X / 2;
    cabeca.y = MAX_tela_y / 2;
    imagem[cabeca.y][cabeca.x] = forma_cabeca;
}

void inicia_comida() {
    comida.x = rand() % (MAX_tela_X - 2) + 1;
    comida.y = rand() % (MAX_tela_y - 2) + 1;
    comida.ativo = 1;
    imagem[comida.y][comida.x] = forma_comida;
}

void colisa_comida() {
    if (comida.ativo && cabeca.x == comida.x && cabeca.y == comida.y) {
        ponto += 10;
        comida.ativo = 0;
        imagem[comida.y][comida.x] = ' ';
        inicia_comida();
        
       
        if (tamanho_corpo < MAX_CORPO) {
            tamanho_corpo++;
        }
    }
}

void colisao_tela() {
    if (cabeca.x == MAX_tela_X - 1 || cabeca.x == 0 || cabeca.y == MAX_tela_y - 1 || cabeca.y == 0) {
        exit(1);
    }
}

void colisao_corpo() {
    for (int i = 0; i < tamanho_corpo; i++) {
        if (cabeca.x == corpo[i].x && cabeca.y == corpo[i].y) {
            exit(1);
        }
    }
}

void mover_cobra() {
    
    if (tamanho_corpo > 0) {
        imagem[corpo[tamanho_corpo - 1].y][corpo[tamanho_corpo - 1].x] = ' ';
    }

   
    for (int i = tamanho_corpo - 1; i > 0; i--) {
        corpo[i] = corpo[i - 1];
    }

   
    if (tamanho_corpo > 0) {
        corpo[0].x = cabeca.x;
        corpo[0].y = cabeca.y;
    }

    imagem[cabeca.y][cabeca.x] = ' ';

    if (kbhit()) {
        char move = getch();
        if (move == 'a' && direcao_x == 0) { direcao_x = -1; direcao_y = 0; }
        if (move == 'd' && direcao_x == 0) { direcao_x = 1; direcao_y = 0; }
        if (move == 'w' && direcao_y == 0) { direcao_x = 0; direcao_y = -1; }
        if (move == 's' && direcao_y == 0) { direcao_x = 0; direcao_y = 1; }
    }

    cabeca.x += direcao_x;
    cabeca.y += direcao_y;
    imagem[cabeca.y][cabeca.x] = forma_cabeca;

    
    for (int i = 0; i < tamanho_corpo; i++) {
        imagem[corpo[i].y][corpo[i].x] = forma_corpo;
    }
}

int main() {
    srand(time(NULL));
    inicia_cobra();
    inicia_comida();
    while (1) {
        limpar();
        tela();
        colisa_comida();
        mover_cobra();
        colisao_tela();
        colisao_corpo();
        usleep(ATRASO_TIQUE-(ponto*100));
    }
}
