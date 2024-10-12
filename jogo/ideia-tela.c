#include <ncurses.h>
#include <unistd.h> // Para a função sleep()

void iniciar_tela() {
    initscr();            // Inicia o modo ncursesaa
    noecho();             // Não mostrar teclas pressionadas
    curs_set(FALSE);      // Esconde o cursor
}

void mostrar_titulo() {
   const char *game_over[] = {
    "  _____                         ____                  ",
    " / ____|                       / __ \\                 ",
    "| |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __  ",
    "| | |_ |/ _` | '_ ` _ \\ / _ \\ | |  | \\ \\ / / _ \\ '__| ",
    "| |__| | (_| | | | | | |  __/ | |__| |\\ V /  __/ |    ",
    " \\_____|\__,_|_| |_| |_|\\___|  \\____/  \\_/ \\___|_|    ",
    "                                                      ",
    "====================== PRESS ENTER ======================="
};

    int linhas = 8; // Número de linhas do título
    int x, y;
    getmaxyx(stdscr, y, x); // Pega o tamanho atual da tela

    // Centraliza o título na tela
    for (int i = 0; i < linhas; i++) {
        mvprintw((y / 2 - linhas / 2) + i, (x - 55) / 2, "%s", game_over[i]);
    }

    refresh();
}

void esperar_tecla() {
    while (1) {
        int ch = getch();
        if (ch == '\n' || ch == '\r') { // Enter pressionado
            break;
        }
    }
}
void iniciar(){
    iniciar_tela();
    mostrar_titulo();

    // Espera o jogador pressionar Enter
    esperar_tecla();

    // Limpa a tela e inicia o jogo (simulação)
    clear();
    mvprintw(10, 10, "carregando...");
    refresh();
    sleep(2); // Pausa para simulação

    endwin(); // Finaliza o modo ncurses
}

int main() {
    iniciar();
    return 0;
}
