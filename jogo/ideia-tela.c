#include <ncurses.h>
#include <unistd.h> // Para a função sleep()

void iniciar_tela() {
    initscr();            // Inicia o modo ncursesaa
    noecho();             // Não mostrar teclas pressionadas
    curs_set(FALSE);      // Esconde o cursor
}

void mostrar_titulo() {
    char *titulo[] = {
        "  _____                      _____           _           ",
        " / ____|                    ||_   _|         (_)          ",
        "| (___   ___  _ __ ___  _ __   | |  _ __  ___ _  ___  _ __ ",
        " \\___ \\ / _ \\| '_ ` _ \\| '_ \\  | | | '_ \\/ __| |/ _ \\| '_ \\",
        " ____) | (_) | | | | | | |_) |_| |_| | | \\__ \\ | (_) | | | |",
        "|_____/ \\___/|_| |_| |_| .__/|_____|_| |_|___/_|\\___/|_| |_|",
        "                      | |                                 ",
        "                      |_|                                 ",
        "====================== PRESS ENTER ========================"
    };

    int linhas = 9; // Número de linhas do título
    int x, y;
    getmaxyx(stdscr, y, x); // Pega o tamanho atual da tela

    // Centraliza o título na tela
    for (int i = 0; i < linhas; i++) {
        mvprintw((y / 2 - linhas / 2) + i, (x - 55) / 2, "%s", titulo[i]);
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

int main() {
    iniciar_tela();
    mostrar_titulo();

    // Espera o jogador pressionar Enter
    esperar_tecla();

    // Limpa a tela e inicia o jogo (simulação)
    clear();
    mvprintw(10, 10, "Iniciando o jogo...");
    refresh();
    sleep(2); // Pausa para simulação

    endwin(); // Finaliza o modo ncurses
    return 0;
}
