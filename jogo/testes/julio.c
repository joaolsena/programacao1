#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Para usar a função usleep()
#include <ncurses.h>
#include <time.h>

#define LARGURA 40
#define ALTURA 20
#define SIMBOLO_DVD "DVD"
#define ATRASO_TIQUE 100000 // microsegundos (100 mil microssegundos = 100 ms)

// Estrutura para representar o logotipo "DVD" e sua posição/direção
typedef struct {
    int x, y;
    int dx, dy;
    int cor;
} DVD;

DVD dvd;

// Função para reinicializar o logotipo "DVD" em uma posição e direção aleatória
void reiniciar_dvd() {
    dvd.x = rand() % (LARGURA - 3); // -3 porque o "DVD" tem 3 caracteres
    dvd.y = rand() % ALTURA;
    dvd.dx = (rand() % 2 == 0) ? 1 : -1;
    dvd.dy = (rand() % 2 == 0) ? 1 : -1;
    dvd.cor = 1; // Inicializa com a primeira cor
}

// Função para desenhar o logotipo na tela
void desenhar_tela() {
    clear(); // Limpa a tela

    // Muda a cor do logotipo
    attron(COLOR_PAIR(dvd.cor));
    
    // Desenha o logotipo "DVD" na posição atual
    mvprintw(dvd.y, dvd.x, SIMBOLO_DVD);
    
    // Desativa a cor
    attroff(COLOR_PAIR(dvd.cor));

    refresh(); // Atualiza a tela
}

// Função para garantir que cores iguais não se repitam em sequência
void alterar_cor() {
    int nova_cor;
    do {
        nova_cor = rand() % 7 + 1; // Gera cores de 1 a 7
    } while (nova_cor == dvd.cor);
    dvd.cor = nova_cor;
}

// Função para atualizar a posição do logotipo "DVD"
void atualizar_posicao_dvd() {
    dvd.x += dvd.dx;
    dvd.y += dvd.dy;

    if (dvd.x <= 0 || dvd.x >= LARGURA - 3) { // -3 porque o "DVD" tem 3 caracteres
        dvd.dx *= -1;
        alterar_cor();
    }
    if (dvd.y <= 0 || dvd.y >= ALTURA - 1) {
        dvd.dy *= -1;
        alterar_cor();
    }
}

int main() {
    srand(time(NULL));
    initscr(); // Inicia a tela do ncurses
    curs_set(0); // Esconde o cursor
    noecho(); // Não mostra os caracteres digitados

    // Verifica se o terminal suporta cores
    if (has_colors()) {
        start_color();
        // Define pares de cores
        init_pair(1, COLOR_RED, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        init_pair(3, COLOR_YELLOW, COLOR_BLACK);
        init_pair(4, COLOR_BLUE, COLOR_BLACK);
        init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(6, COLOR_CYAN, COLOR_BLACK);
        init_pair(7, COLOR_WHITE, COLOR_BLACK);
    }

    // Reinicia a posição e direção do logotipo
    reiniciar_dvd();

    while (1) {
        atualizar_posicao_dvd();
        desenhar_tela();
        usleep(ATRASO_TIQUE); // Pausa de 100 milissegundos (100 ms)
        
        // Se o usuário pressionar 'q', encerra o programa
        if (getch() == 'q') break;
    }

    endwin(); // Finaliza o ncurses
    return 0;
}
