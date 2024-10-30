#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <termios.h>

void configurar_terminal() {
    struct termios new_settings;
    tcgetattr(0, &new_settings); // Obtém os atributos atuais do terminal
    new_settings.c_lflag &= ~ICANON; // Desativa o modo canônico
    new_settings.c_lflag &= ~ECHO; // Desativa a exibição de caracteres
    tcsetattr(0, TCSANOW, &new_settings); // Aplica as novas configurações
}

void resetar_terminal() {
    struct termios original_settings;
    tcgetattr(0, &original_settings); // Obtém os atributos atuais do terminal
    original_settings.c_lflag |= ICANON; // Ativa o modo canônico
    original_settings.c_lflag |= ECHO; // Ativa a exibição de caracteres
    tcsetattr(0, TCSANOW, &original_settings); // Restaura as configurações
}

void tocar_musica_fundo(const char *arquivo_som) {
    char *args[] = {"afplay", (char *)arquivo_som, NULL};
    execvp("afplay", args); // Substitui o processo por afplay
    perror("Erro ao tocar a música"); // Em caso de falha
    exit(1); // Sai se execvp falhar
}

int main() {
    // Configurar terminal para entrada sem enter
    configurar_terminal();
    
    // Cria um processo filho para tocar música em loop
    pid_t pid_musica = fork();
    if (pid_musica == 0) { // Processo filho toca a música
        while (1) {
            tocar_musica_fundo("/Users/user01/Documents/GitHub/programacao1/jogo/sons/musica-jogo.mp3");
        }
    } else if (pid_musica < 0) {
        perror("Erro ao criar o processo de música");
        return 1;
    }

    // Loop do jogo
    printf("Pressione '1' para sair do jogo e parar a música.\n");
    while (1) {
        if (getchar() == '1') break; // Sai do loop ao pressionar '1'
    }

    // Parar a música quando o jogo acabar
    kill(pid_musica, SIGKILL); // Envia SIGKILL ao processo filho
    printf("Música de fundo parada.\n");

    // Restaura as configurações do terminal antes de sair
    resetar_terminal();

    return 0;
}
