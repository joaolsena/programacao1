#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Definições para a tela de visualização
#define MAX_HEIGHT 10
#define LARGURA_TELA 80
#define ALTURA_TELA 20

typedef struct Node {
    int chaveEsquerda;          // Primeira chave
    int chaveDireita;           // Segunda chave
    struct Node *esquerda;      // Filho esquerdo
    struct Node *meio;          // Filho do meio
    struct Node *direita;       // Filho direito
    int numChaves;              // Número de chaves (1 ou 2)
    bool ehFolha;              // Indica se é nó folha
} Node;

// Estrutura para a tela de visualização
typedef struct {
    char **tela;
    int altura;
    int largura;
} TelaVisualizacao;

/// Função auxiliar para criar um novo nó
Node* criarNo(int chave, bool ehFolha) {
    Node* novo = (Node*)malloc(sizeof(Node));
    novo->chaveEsquerda = chave;
    novo->chaveDireita = -1;
    novo->esquerda = NULL;
    novo->meio = NULL;
    novo->direita = NULL;
    novo->numChaves = 1;
    novo->ehFolha = ehFolha;
    return novo;
}

// Função para buscar uma chave na árvore
bool buscar(Node* raiz, int chave) {
    if (raiz == NULL) return false;
    
    // Verifica se a chave está no nó atual
    if (chave == raiz->chaveEsquerda || 
        (raiz->numChaves == 2 && chave == raiz->chaveDireita)) {
        return true;
    }
    
    // Se é folha e não encontrou, retorna falso
    if (raiz->ehFolha) return false;
    
    // Navega para o filho apropriado
    if (chave < raiz->chaveEsquerda) {
        return buscar(raiz->esquerda, chave);
    } else if (raiz->numChaves == 2 && chave > raiz->chaveDireita) {
        return buscar(raiz->direita, chave);
    } else {
        return buscar(raiz->meio, chave);
    }
}

// Função auxiliar para dividir um nó folha
Node* dividirNoFolha(Node* no, int chave, int* chavePromovida) {
    // Organiza as três chaves em ordem
    int valores[3];
    if (chave < no->chaveEsquerda) {
        valores[0] = chave;
        valores[1] = no->chaveEsquerda;
        valores[2] = no->chaveDireita;
    } else if (chave < no->chaveDireita) {
        valores[0] = no->chaveEsquerda;
        valores[1] = chave;
        valores[2] = no->chaveDireita;
    } else {
        valores[0] = no->chaveEsquerda;
        valores[1] = no->chaveDireita;
        valores[2] = chave;
    }
    
    // Cria novo nó para a direita
    Node* novoNo = criarNo(valores[2], true);
    
    // Atualiza nó original (esquerda)
    no->chaveEsquerda = valores[0];
    no->chaveDireita = -1;
    no->numChaves = 1;
    
    // Define a chave que será promovida
    *chavePromovida = valores[1];
    
    return novoNo;
}

// Função auxiliar para dividir um nó interno
Node* dividirNoInterno(Node* no, int chave, Node* novoFilho, int* chavePromovida) {
    int valores[3];
    Node* ponteiros[4];
    
    // Organiza as chaves e ponteiros
    if (chave < no->chaveEsquerda) {
        valores[0] = chave;
        valores[1] = no->chaveEsquerda;
        valores[2] = no->chaveDireita;
        ponteiros[0] = novoFilho->esquerda;
        ponteiros[1] = novoFilho->meio;
        ponteiros[2] = no->meio;
        ponteiros[3] = no->direita;
    } else if (no->numChaves == 1 || chave < no->chaveDireita) {
        valores[0] = no->chaveEsquerda;
        valores[1] = chave;
        valores[2] = no->chaveDireita;
        ponteiros[0] = no->esquerda;
        ponteiros[1] = novoFilho->esquerda;
        ponteiros[2] = novoFilho->meio;
        ponteiros[3] = no->direita;
    } else {
        valores[0] = no->chaveEsquerda;
        valores[1] = no->chaveDireita;
        valores[2] = chave;
        ponteiros[0] = no->esquerda;
        ponteiros[1] = no->meio;
        ponteiros[2] = novoFilho->esquerda;
        ponteiros[3] = novoFilho->meio;
    }
    
    // Cria novo nó para a direita
    Node* novoNo = criarNo(valores[2], false);
    novoNo->esquerda = ponteiros[2];
    novoNo->meio = ponteiros[3];
    
    // Atualiza nó original (esquerda)
    no->chaveEsquerda = valores[0];
    no->chaveDireita = -1;
    no->numChaves = 1;
    no->esquerda = ponteiros[0];
    no->meio = ponteiros[1];
    no->direita = NULL;
    
    // Define a chave que será promovida
    *chavePromovida = valores[1];
    
    return novoNo;
}

// Função auxiliar para inserir em nó interno
Node* inserirNoInterno(Node* no, int chave, Node* novoFilho) {
    if (no->numChaves == 1) {
        // Tem espaço no nó
        if (chave < no->chaveEsquerda) {
            no->chaveDireita = no->chaveEsquerda;
            no->chaveEsquerda = chave;
            no->direita = no->meio;
            no->meio = novoFilho->meio;
            no->esquerda = novoFilho->esquerda;
        } else {
            no->chaveDireita = chave;
            no->direita = novoFilho->meio;
            no->meio = novoFilho->esquerda;
        }
        no->numChaves = 2;
        free(novoFilho);
        return no;
    } else {
        // Precisa dividir o nó
        int chavePromovida;
        Node* novoNo = dividirNoInterno(no, chave, novoFilho, &chavePromovida);
        
        // Cria novo nó pai
        Node* novoPai = criarNo(chavePromovida, false);
        novoPai->esquerda = no;
        novoPai->meio = novoNo;
        return novoPai;
    }
}

// Função principal de inserção
Node* inserir(Node* raiz, int chave) {
    // Verifica se a chave já existe
    if (buscar(raiz, chave)) {
        printf("Chave %d já existe na árvore.\n", chave);
        return raiz;
    }
    
    // Árvore vazia
    if (raiz == NULL) {
        return criarNo(chave, true);
    }
    
    // Se é folha
    if (raiz->ehFolha) {
        if (raiz->numChaves == 1) {
            // Tem espaço no nó
            if (chave < raiz->chaveEsquerda) {
                raiz->chaveDireita = raiz->chaveEsquerda;
                raiz->chaveEsquerda = chave;
            } else {
                raiz->chaveDireita = chave;
            }
            raiz->numChaves = 2;
            return raiz;
        } else {
            // Precisa dividir o nó
            int chavePromovida;
            Node* novoNo = dividirNoFolha(raiz, chave, &chavePromovida);
            
            // Cria novo nó pai
            Node* novoPai = criarNo(chavePromovida, false);
            novoPai->esquerda = raiz;
            novoPai->meio = novoNo;
            return novoPai;
        }
    }
    
    // Se não é folha, navega recursivamente
    Node* filho = NULL;
    Node* novoFilho = NULL;
    
    if (chave < raiz->chaveEsquerda) {
        filho = inserir(raiz->esquerda, chave);
        if (filho != raiz->esquerda) {
            novoFilho = filho;
            return inserirNoInterno(raiz, novoFilho->chaveEsquerda, novoFilho);
        }
        raiz->esquerda = filho;
    } else if (raiz->numChaves == 2 && chave > raiz->chaveDireita) {
        filho = inserir(raiz->direita, chave);
        if (filho != raiz->direita) {
            novoFilho = filho;
            return inserirNoInterno(raiz, novoFilho->chaveEsquerda, novoFilho);
        }
        raiz->direita = filho;
    } else {
        filho = inserir(raiz->meio, chave);
        if (filho != raiz->meio) {
            novoFilho = filho;
            return inserirNoInterno(raiz, novoFilho->chaveEsquerda, novoFilho);
        }
        raiz->meio = filho;
    }
    
    return raiz;
}

// Função para percorrer a árvore em ordem (In-Order)
void percorrerEmOrdem(Node* raiz) {
    if (raiz == NULL) return;

    percorrerEmOrdem(raiz->esquerda);
    printf("%d ", raiz->chaveEsquerda);
    if (raiz->numChaves == 2) {
        percorrerEmOrdem(raiz->meio);
        printf("%d ", raiz->chaveDireita);
    } else {
        percorrerEmOrdem(raiz->meio);
    }
    percorrerEmOrdem(raiz->direita);
}

// Função para percorrer a árvore por nível (Level-Order)
void percorrerPorNivel(Node* raiz) {
    if (raiz == NULL) return;

    Node* fila[100];
    int inicio = 0, fim = 0;
    fila[fim++] = raiz;

    while (inicio < fim) {
        Node* atual = fila[inicio++];
        printf("|%d ", atual->chaveEsquerda);
        if (atual->numChaves == 2) {
            printf("%d ", atual->chaveDireita);
        }

        if (!atual->ehFolha) {
            fila[fim++] = atual->esquerda;
            fila[fim++] = atual->meio;
            if (atual->numChaves == 2) {
                fila[fim++] = atual->direita;
            }
        }
    }
}

// Função para desenhar um nó na tela
void desenharNo(TelaVisualizacao *tela, Node *node, int linha, int coluna) {
    if (!node) return;

    char nodeStr[20];
    if (node->numChaves == 2) {
        sprintf(nodeStr, "[%d|%d]", node->chaveEsquerda, node->chaveDireita);
    } else {
        sprintf(nodeStr, "[%d]", node->chaveEsquerda);
    }

    // Centraliza o nó na posição
    int len = strlen(nodeStr);
    int start = coluna - len / 2;
    for (int i = 0; i < len; i++) {
        if (start + i >= 0 && start + i < tela->largura) {
            tela->tela[linha][start + i] = nodeStr[i];
        }
    }
}

// Função para desenhar as conexões entre os nós
void desenharConexoes(TelaVisualizacao *tela, int linhaPai, int colunaPai,
                      int linhaFilho, int colunaFilho, bool ehMeio, bool ehNoPaiDuplo) {
    if (ehMeio) {
        // Centraliza a linha vertical baseado no tipo do nó pai
        int ajuste = ehNoPaiDuplo ? 0 : 1;
        for (int i = 1; i < linhaFilho - linhaPai; i++) {
            tela->tela[linhaPai + i][colunaPai + ajuste] = '|';
        }
    } else {
        int distancia = abs(colunaFilho - colunaPai);
        int direcao = (colunaFilho < colunaPai) ? -1 : 1;
        // Sempre usa '/' para esquerda e '\' para direita, independente do tipo de nó
        char simbolo = (direcao < 0) ? '/' : '\\';

        // Ajusta o ponto inicial para nós simples
        if (!ehNoPaiDuplo) {
            colunaPai += (direcao < 0) ? -1 : 1;
        }

        for (int i = 1; i < linhaFilho - linhaPai; i++) {
            int col = colunaPai + (direcao * i * distancia) / (linhaFilho - linhaPai);
            if (col >= 0 && col < tela->largura) {
                tela->tela[linhaPai + i][col] = simbolo;
            }
        }
    }
}

// Função recursiva para desenhar a árvore
void desenharArvoreRecursivo(TelaVisualizacao *tela, Node *node, int nivel, int coluna) {
    if (!node) return;

    int linha = nivel * 3;
    bool ehNoDuplo = node->numChaves == 2;
    desenharNo(tela, node, linha, coluna);

    if (!node->ehFolha) {
        int espacamento = 20 / (nivel + 1);

        // Ajusta espaçamento baseado no tipo do nó
        if (!ehNoDuplo) {
            espacamento = (espacamento * 4) / 5;
        }

        int colunaEsq = coluna - espacamento;
        int colunaDir = coluna + espacamento;

        // Desenha filho esquerdo
        desenharArvoreRecursivo(tela, node->esquerda, nivel + 1, colunaEsq);
        desenharConexoes(tela, linha, coluna, linha + 3, colunaEsq, false, ehNoDuplo);

        if (ehNoDuplo) {
            // Para nó duplo [A|B]:
            // - ponteiroDoMeio liga com a primeira chave
            // - ponteiroDaDireita liga com a segunda chave
            desenharArvoreRecursivo(tela, node->meio, nivel + 1, coluna);
            desenharConexoes(tela, linha, coluna, linha + 3, coluna, true, ehNoDuplo);

            desenharArvoreRecursivo(tela, node->direita, nivel + 1, colunaDir);
            desenharConexoes(tela, linha, coluna, linha + 3, colunaDir, false, ehNoDuplo);
        } else {
            // Para nó simples [A]:
            // - ponteiroDoMeio é tratado como filho direito
            // - ponteiroDaDireita não é usado
            desenharArvoreRecursivo(tela, node->meio, nivel + 1, colunaDir);
            desenharConexoes(tela, linha, coluna, linha + 3, colunaDir, false, ehNoDuplo);
        }
    }
}

// Função para imprimir a árvore de forma visual
void imprimirArvore(Node *raiz) {
    if (!raiz) {
        printf("\n=== Árvore 2-3 Vazia ===\n");
        return;
    }

    TelaVisualizacao *tela = malloc(sizeof(TelaVisualizacao));
    tela->altura = ALTURA_TELA;
    tela->largura = LARGURA_TELA;

    // Inicializa a tela com espaços
    tela->tela = malloc(ALTURA_TELA * sizeof(char *));
    for (int i = 0; i < ALTURA_TELA; i++) {
        tela->tela[i] = malloc(LARGURA_TELA * sizeof(char));
        memset(tela->tela[i], ' ', LARGURA_TELA);
    }

    printf("\n=== Árvore 2-3 ===\n\n");

    // Começa o desenho no centro da tela
    desenharArvoreRecursivo(tela, raiz, 0, LARGURA_TELA / 2);

    // Imprime a visualização
    for (int i = 0; i < tela->altura; i++) {
        bool linhaVazia = true;
        for (int j = 0; j < tela->largura; j++) {
            if (tela->tela[i][j] != ' ') {
                linhaVazia = false;
                break;
            }
        }
        if (linhaVazia) continue;

        for (int j = 0; j < tela->largura; j++) {
            printf("%c", tela->tela[i][j]);
        }
        printf("\n");
    }

    // Libera a memória
    for (int i = 0; i < tela->altura; i++) {
        free(tela->tela[i]);
    }
    free(tela->tela);
    free(tela);
}

// Função para exibir o menu
void exibirMenu() {
    printf("\n--- Menu ---\n");
    printf("1. Inserir número\n");
    printf("2. Ver árvore em ordem\n");
    printf("3. Ver árvore por nível\n");
    printf("4. Buscar número\n");
    printf("5. Ver árvore visualmente\n");
    printf("6. Sair\n");
    printf("Escolha uma opção: ");
}

// Função principal
int main() {
    Node* raiz = NULL;
    int opcao, valor;

    while (1) {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o número a ser inserido: ");
                scanf("%d", &valor);
                raiz = inserir(raiz, valor);
                break;

            case 2:
                printf("Árvore em ordem: ");
                percorrerEmOrdem(raiz);
                printf("\n");
                break;

            case 3:
                printf("Árvore por nível: ");
                percorrerPorNivel(raiz);
                printf("\n");
                break;

            case 4:
                printf("Digite o número a ser buscado: ");
                scanf("%d", &valor);
                if (buscar(raiz, valor)) {
                    printf("Número %d encontrado na árvore.\n", valor);
                } else {
                    printf("Número %d não encontrado na árvore.\n", valor);
                }
                break;

            case 5:
                imprimirArvore(raiz);
                break;

            case 6:
                printf("Saindo...\n");
                exit(0);

            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    }

    return 0;
}