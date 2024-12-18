#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int getch(void) {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);            // Pega os atributos atuais do terminal
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);          // Desabilita o modo de buffer e eco de caracteres
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);   // Define os novos atributos do terminal
    ch = getchar();                            // Lê um caractere
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);   // Restaura os atributos antigos do terminal
    return ch;
}

int main() {
    for (int i = 0; i < 5; i++)
    {
       
    
    printf("Pressione uma tecla...\n");
    char c = getch();                          // Ler a tecla
    printf("Você pressionou: %c\n", c);
    }
    return 0;
}
