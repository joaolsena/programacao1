// lista de coisas que faltam ser implementadas
// Tiros inimigos que também possam destruir barreiras e atingir o jogador; Sistema de níveis com aumento de dificuldade e tela de game over e tela inicial E DEIXAR ESSA BOMBA FLUIDA

#include <stdio.h>
#include <stdlib.h>

// Configurações de tela
#define MAX_tela_X 50
#define MAX_tela_y 30
#define MAX_margem 30

// Configurações de jogo
#define forma_jogador '^'
#define forma_tiro '|'
#define max_tiros 3
#define monstro_1 'M'
#define monstro_2 'A'
#define monstro_3 'w'
#define coilisao_monstro 'x'
#define MAX_monstro 10 // Máximo de monstros por linha

//config barreiras
#define barreira_forma_1 '#'
#define barreira_forma_2 '*'
#define barreira_forma_3 '.'
#define max_barreira 49
#define max_grupo 4
#define max_barreiras_por_grupo 6 
#define  max_espaco_grupo 4

int ponto = 0;
int vida = 3;
int direcao = 1;
int tempo_monstro = 0;
int velocidade = 1;

char imagem[MAX_tela_y][MAX_tela_X] = {0};

// Estruturas para tiros, monstros e jogador
typedef struct {
    int ativo;
    int x;
    int y;
} tiros;

tiros tiro[max_tiros] = {{0, 0, 0}};

typedef struct {
    int ativo;
    int x;
    int y;
} bicho;

bicho monstro[MAX_monstro * 2] = {{0, 0, 0}}; 

typedef struct {
    int ativo;
    int x;
    int y;
} bicho2;

bicho2 monstro2[MAX_monstro*2] = {{0, 0, 0}}; 

typedef struct {
    int ativo;
    int x;
    int y;
} bicho3;

bicho3 monstro3[MAX_monstro] = {{0, 0, 0}};

typedef struct {
    int x;
    int y;
} jogado;

jogado jogador_p;

typedef struct {
    int ativo;
    int x;
    int y;
    int resistencia;
} barreira;

barreira barreiras[max_barreira] = {{0, 0, 0, 0}};

// Função para limpar a tela
void limpar() {
    system("clear"); // Usar "cls" no Windows
}

// Função para desenhar a tela
void tela() {
    printf("%*sPontos: %d", MAX_margem + 15, " ", ponto);
    printf("%*sVida: %d\n", MAX_margem + 15, "", vida);
    
    for (int i = 0; i < MAX_tela_y; i++) {
        for (int k = 0; k < MAX_margem; k++) {
            printf("  ");
        }
        for (int j = 0; j < MAX_tela_X; j++) {
            if (i == MAX_tela_y - 1) {
                printf("_");
            } else if (imagem[i][j] == forma_jogador) {
                printf("%c", forma_jogador);
            } else if (imagem[i][j] == monstro_1 || imagem[i][j] == monstro_2 || imagem[i][j] == monstro_3) {
                printf("%c", imagem [i][j]);
            } else if (imagem[i][j] == barreira_forma_1 || imagem[i][j] == barreira_forma_2 || imagem [i][j]== barreira_forma_3) {
                printf("%c", imagem[i][j]);
             } else if (imagem[i][j] == forma_tiro) {
                printf("%c", forma_tiro);
            } else {
                printf(" ");
            }
        }
        putchar('\n');
    }
}

// Função para inicializar o jogador
void inicia_jogador() {
    jogador_p.x = MAX_tela_X / 2;
    jogador_p.y = MAX_tela_y - 2;
    imagem[jogador_p.y][jogador_p.x] = forma_jogador;
}

// Função para inicializar monstros
void inicia_monstros() {
    for (int i = 0; i < MAX_monstro; i++) {
        
        monstro[i].ativo = 1;
        monstro[i].x = (MAX_tela_X / 10) + (2 * i);
        monstro[i].y = MAX_tela_y / 2;
        imagem[monstro[i].y][monstro[i].x] = monstro_1;

        monstro[i + MAX_monstro].ativo = 1;
        monstro[i + MAX_monstro].x = (MAX_tela_X / 10) + (2 * i);
        monstro[i + MAX_monstro].y = (MAX_tela_y / 2) - 1;
        imagem[monstro[i + MAX_monstro].y][monstro[i + MAX_monstro].x] = monstro_1;

        
        monstro2[i].ativo = 1;
        monstro2[i].x = (MAX_tela_X / 10) + (2 * i);
        monstro2[i].y = (MAX_tela_y / 2) - 2;
        imagem[monstro2[i].y][monstro2[i].x] = monstro_2;

        monstro2[i+MAX_monstro].ativo = 1;
        monstro2[i+MAX_monstro].x = (MAX_tela_X / 10) + (2 * i);
        monstro2[i+ MAX_monstro].y = (MAX_tela_y / 2) - 3;
        imagem[monstro2[i + MAX_monstro].y][monstro2[i + MAX_monstro].x] = monstro_2;

        monstro3[i].ativo = 1;
        monstro3[i].x = (MAX_tela_X / 10) + (2 * i);
        monstro3[i].y = (MAX_tela_y / 2) - 4;
        imagem[monstro3[i].y][monstro3[i].x] = monstro_3;

    }
}

void inicia_barreira() {
    int inicio_grupo = (MAX_tela_X - (max_grupo * max_barreiras_por_grupo) - ((max_grupo - 1) * max_espaco_grupo)) / 2;
    int barreira_contagem = 0;

    for (int i = 0; i < max_grupo; i++) {
        for (int j = 0; j < max_barreiras_por_grupo; j++) {
            barreiras[barreira_contagem].ativo = 1;
            barreiras[barreira_contagem].x = inicio_grupo + (i * (max_barreiras_por_grupo + max_espaco_grupo)) + j;
            barreiras[barreira_contagem].y = MAX_tela_y - 5;
            barreiras[barreira_contagem].resistencia = 10;
            
            imagem[barreiras[barreira_contagem].y][barreiras[barreira_contagem].x] = barreira_forma_1;
            
            barreira_contagem++;
        }
    }
}
void configuracoes_iniciais(){
    inicia_jogador();
    inicia_monstros();
    inicia_barreira();
}
// Função para disparar tiros
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
// Função para mover monstros e atualizar suas posições
void limpa_posicao_monstros() {
    for (int i = 0; i < MAX_monstro * 2; i++) {
        if (monstro[i].ativo) imagem[monstro[i].y][monstro[i].x] = ' ';
        if (monstro2[i].ativo) imagem[monstro2[i].y][monstro2[i].x] = ' ';
        if (i < MAX_monstro && monstro3[i].ativo) imagem[monstro3[i].y][monstro3[i].x] = ' ';
    }
}

void atualiza_posicao_monstros() {
    for (int i = 0; i < MAX_monstro * 2; i++) {
        if (monstro[i].ativo) monstro[i].x += direcao;
        if (monstro2[i].ativo) monstro2[i].x += direcao;
        if (i < MAX_monstro && monstro3[i].ativo) monstro3[i].x += direcao;
    }
}

void desce_linha_monstros() {
    for (int i = 0; i < MAX_monstro * 2; i++) {
        if (monstro[i].ativo) monstro[i].y += 1;
        if (monstro2[i].ativo) monstro2[i].y += 1;
        if (i < MAX_monstro && monstro3[i].ativo) monstro3[i].y += 1;

        if ((monstro[i].y >= MAX_tela_y - 3 || monstro2[i].y >= MAX_tela_y - 3 || monstro3[i].y >= MAX_tela_y - 3) && vida > 0) {
            vida--;
            if (vida == 0) {
                printf("\nGame Over!\n");
                exit(0);
            }
        }
    }
}

void desenha_monstros_na_tela() {
    for (int i = 0; i < MAX_monstro * 2; i++) {
        if (monstro[i].ativo) imagem[monstro[i].y][monstro[i].x] = monstro_1;
        if (monstro2[i].ativo) imagem[monstro2[i].y][monstro2[i].x] = monstro_2;
        if (i < MAX_monstro && monstro3[i].ativo) imagem[monstro3[i].y][monstro3[i].x] = monstro_3;
    }
}

void verifica_bordas_e_atualiza_direcao() {
    int borda=0;
    for (int i = 0; i < MAX_monstro * 2; i++) {
        if (monstro[i].ativo && (monstro[i].x <= 0 || monstro[i].x >= MAX_tela_X - 1) ||
            monstro2[i].ativo && (monstro2[i].x <= 0 || monstro2[i].x >= MAX_tela_X - 1) ||
            i < MAX_monstro && monstro3[i].ativo && (monstro3[i].x <= 0 || monstro3[i].x >= MAX_tela_X - 1)) {
            borda=1;
            velocidade++; 
            break;  
        }
    }

    if(borda){
        direcao *= -1;
            desce_linha_monstros();     
    }
}
void velocidade_monstro(){
    int monstros_ativos = 0;
     // Contagem de monstros do tipo 1 e 2
    for (int i = 0; i < MAX_monstro * 2; i++) {
        if (monstro[i].ativo) monstros_ativos++;
        if (monstro2[i].ativo) monstros_ativos++;
    }
    
    for (int i = 0; i < MAX_monstro; i++) {
        if (monstro3[i].ativo) monstros_ativos++;
    }

    // Ajuste da velocidade com limite
    if (monstros_ativos < (MAX_monstro * 5)/2) {  
        if (velocidade <7)
        {
          velocidade++;
        }   
    }
}

void movimento_monstro() {
   tempo_monstro++;
if (tempo_monstro >= (10 - velocidade)) {
    tempo_monstro = 0;
        velocidade_monstro();
        limpa_posicao_monstros();
        atualiza_posicao_monstros();
        verifica_bordas_e_atualiza_direcao();
        desenha_monstros_na_tela();
    }
}

// Função para mover o jogador e processar disparos
void mover() {
    imagem[jogador_p.y][jogador_p.x] = ' ';
    char move;
    move = getchar();  

    if (move == 'a' && jogador_p.x > 1) {
        jogador_p.x--;
    } else if (move == 'd' && jogador_p.x < MAX_tela_X - 2) {
        jogador_p.x++;
    } else if (move == ' ') {
        disparos();
    } else if (move == 'q') {
        exit(0);
    }

    imagem[jogador_p.y][jogador_p.x] = forma_jogador;
    movimento_monstro();
}

void colisao_com_monstro(){

for (int i = 0; i < max_tiros; i++) {
        if (tiro[i].ativo) {
            for (int j = 0; j < MAX_monstro * 2; j++) {
                if (monstro[j].ativo && tiro[i].x == monstro[j].x && tiro[i].y == monstro[j].y) {
                    ponto += 10; 
                    monstro[j].ativo = 0;
                    imagem[monstro[j].y][monstro[j].x] = ' ';
                    tiro[i].ativo = 0;
                    break; 
                }
            }

            
            for (int j = 0; j < MAX_monstro*2; j++) {
                if (monstro2[j].ativo && tiro[i].x == monstro2[j].x && tiro[i].y == monstro2[j].y) {
                    ponto += 20; 
                    monstro2[j].ativo = 0;
                    imagem[monstro2[j].y][monstro2[j].x] = ' ';
                    tiro[i].ativo = 0;
                    break; 
                }
            }
            for (int j = 0; j < MAX_monstro; j++) {
                if (monstro3[j].ativo && tiro[i].x == monstro3[j].x && tiro[i].y == monstro3[j].y) {
                    ponto += 40; 
                    monstro3[j].ativo = 0;
                    imagem[monstro3[j].y][monstro3[j].x] = ' ';
                    tiro[i].ativo = 0;
                    break; 
                }
            }
        }
    }
}
void colisao_com_barreiras() {
    for (int i = 0; i < max_tiros; i++) {
        if (tiro[i].ativo) {
            for (int j = 0; j < max_barreira; j++) {
                if (barreiras[j].ativo && 
                    tiro[i].x == barreiras[j].x && 
                    tiro[i].y == barreiras[j].y) {
        
                    barreiras[j].resistencia--;
                    tiro[i].ativo = 0;
                    imagem[tiro[i].y][tiro[i].x] = ' ';
                    if ( barreiras[j].resistencia>7){
                        imagem[barreiras[j].y][barreiras[j].x] = barreira_forma_1;
                    } else if (barreiras[j].resistencia>3 ) {
                        imagem[barreiras[j].y][barreiras[j].x] = barreira_forma_2;
                    } else if (barreiras[j].resistencia>0) {
                        imagem[barreiras[j].y][barreiras[j].x] = barreira_forma_3;
                    } else  {
                        imagem[barreiras[j].y][barreiras[j].x] = ' ';
                        barreiras[j].ativo = 0;
                    }
                }
            }
        }
    }
}


// Função para mover os tiros e verificar colisão com monstros
void tiro_e_colisao() {
    for (int i = 0; i < max_tiros; i++) {
        if (tiro[i].ativo) {
            imagem[tiro[i].y][tiro[i].x] = ' ';

            if (tiro[i].y > 1) {
                tiro[i].y--;
                imagem[tiro[i].y][tiro[i].x] = forma_tiro;
            } else {
                tiro[i].ativo = 0;
            }  
        }
    }
    colisao_com_monstro();
    colisao_com_barreiras();
}

// Função principal do jogo
int main() {
    
    configuracoes_iniciais();

    while (1) {
        limpar();
        tela();
        mover();
        tiro_e_colisao();
    }
    return 0;
}
