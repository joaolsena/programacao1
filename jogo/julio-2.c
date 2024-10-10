#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <unistd.h>

#define LARGURA 80
#define ALTURA 24
#define ALTURA_LOGO 7
#define LARGURA_LOGO 30
#define ATRASO_TIQUE 100

const wchar_t *LOGO_DVD[ALTURA_LOGO] = {
    L"⠀⠀⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⢀⣾⣿⣿⣿⣿⣿⣿⣿⣿⣶⣦⡀",
    L"⠀⢠⣿⣿⡿⠀⠀⠈⢹⣿⣿⡿⣿⣿⣇⠀⣠⣿⣿⠟⣽⣿⣿⠇⠀⠀⢹⣿⣿⣿",
    L"⠀⢸⣿⣿⡇⠀⢀⣠⣾⣿⡿⠃⢹⣿⣿⣶⣿⡿⠋⢰⣿⣿⡿⠀⠀⣠⣼⣿⣿⠏",
    L"⠀⣿⣿⣿⣿⣿⣿⠿⠟⠋⠁⠀⠀⢿⣿⣿⠏⠀⠀⢸⣿⣿⣿⣿⣿⡿⠟⠋⠁⠀",
    L"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣀⣸⣟⣁⣀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
    L"⣠⣴⣶⣾⣿⣿⣻⡟⣻⣿⢻⣿⡟⣛⢻⣿⡟⣛⣿⡿⣛⣛⢻⣿⣿⣶⣦⣄⡀⠀",
    L"⠉⠛⠻⠿⠿⠿⠷⣼⣿⣿⣼⣿⣧⣭⣼⣿⣧⣭⣿⣿⣬⡭⠾⠿⠿⠿⠛⠉⠀"};

typedef struct
{
    int x, y;
    int dx, dy;
    const char *cor; // Altera para uma string que define a cor ANSI

} DVD;

DVD dvd;

void reiniciar_dvd()
{
    dvd.x = rand() % (LARGURA - LARGURA_LOGO);
    dvd.y = rand() % (ALTURA - ALTURA_LOGO);
    dvd.dx = (rand() % 2 == 0) ? 1 : -1;
    dvd.dy = (rand() % 2 == 0) ? 1 : -1;
    dvd.cor = "\033[0;37m"; // Inicializa com cor branca
}

void alterar_cor()
{
    int nova_cor;
    do
    {
        nova_cor = 30 + rand() % 8; // Escolhe uma nova cor entre 30 e 37
    } while (nova_cor == 37); // Evita a cor branca
    char cor_str[10];
    snprintf(cor_str, sizeof(cor_str), "\033[0;%dm", nova_cor);
    dvd.cor = cor_str;
}

void limpar_tela()
{
    // Limpa a tela
    printf("\033[H\033[J"); // ANSI escape para limpar a tela
}

void desenhar_tela()
{
    limpar_tela();

    for (int i = 0; i < ALTURA_LOGO; ++i)
    {
        // Verifica se a linha está dentro dos limites da tela
        if (i + dvd.y < ALTURA)
        {
            // Move o cursor para a posição correta antes de imprimir
            printf("\033[%d;%dH", dvd.y + i, dvd.x + 1);
            printf("%ls", LOGO_DVD[i]); 
        }
    }
}

void atualizar_posicao_dvd()
{
    dvd.x += dvd.dx;
    dvd.y += dvd.dy;

    if (dvd.x <= 0 || dvd.x >= LARGURA - LARGURA_LOGO)
    {
        dvd.dx *= -1;
        alterar_cor();
    }

    if (dvd.y <= 0 || dvd.y >= ALTURA - ALTURA_LOGO)
    {
        dvd.dy *= -1;
        alterar_cor();
    }
}

int main()
{
    setlocale(LC_ALL, "");
    srand(time(NULL));
    reiniciar_dvd();

    while (1)
    {
        atualizar_posicao_dvd();
        desenhar_tela();
        usleep(ATRASO_TIQUE * 1000); // Usar usleep para pausar o loop
    }

    return 0;
}
