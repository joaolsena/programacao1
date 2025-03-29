#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ALTURA_TELA 20
#define LARGURA_TELA 80

// Declarações antecipadas para resolver dependências circulares
typedef struct no No;
typedef struct no_fila NoFila;
typedef struct fila Fila;

// Estrutura para visualização da tela
typedef struct {
    char **tela;
    int altura;
    int largura;
} TelaVisualizacao;

// Estrutura do nó da Árvore 2-3
struct no {
    int chaves[3];
    No *filhos[4];
    int num_chaves;
    bool eh_folha;
};

// Nó para implementação da fila
struct no_fila {
    No *enderecoNo;
    NoFila* proximo;
};

// Estrutura da fila
struct fila {
    NoFila *inicio;
    NoFila *final;
};

// Protótipos de todas as funções
void iniciarFila(Fila *fila);
void enfileirar(Fila *fila, No* no);
No* desenfileirar(Fila *fila);
void liberarFila(Fila *fila);

No* criar_no(int chave, bool eh_folha);
int encontrar_indice_filho(No* no, int valor);
void inserir_chave(No* no, int chave);
void inserir_filho(No* pai, No* filho, int indice);
void dividir_filho(No* pai, int subarvore_sucessora);
No* adicionar_no(No* no, int valor, bool* deve_dividir);
No* dividir_raiz(No* raiz);
No* inserir(No* raiz, int valor);

bool buscar(No *raiz, int valor);
int altura(No *raiz);
void em_ordem(No* raiz);
void em_nivel(No *raiz);

No* remover_valor(No* no, int valor);
No* deletar_item(No* no, int valor);
void remover_chave(No* no, int valor);
No* obter_sucessor(No* no, int chave_interna);
No* redistribuicao_no_simples(No* pai);
No* fusao_no_simples(No* pai, int indice_irmao, int subarvore_sucessora);
No* redistribuicao_no_duplo(No *pai, int indice_filho);
No* fusao_no_duplo(No *pai, int indice_filho);
void rebalancear(No* no, int indice_filho);

void desenharNo(TelaVisualizacao *tela, No *no, int linha, int coluna);
void desenharConexoes(TelaVisualizacao *tela, int linhaPai, int colunaPai,
                      int linhaFilho, int colunaFilho, bool ehMeio, bool ehNoPaiDuplo);
void desenharArvoreRecursivo(TelaVisualizacao *tela, No *no, int nivel, int coluna);
void imprimirArvore(No *raiz);
void menu();

// Iniciar os elementos da fila
void iniciarFila(Fila *fila) {
    fila->inicio = NULL;
    fila->final = NULL;
}

// Insere elementos na fila
void enfileirar(Fila* fila, No* no) {
    NoFila* novo = malloc(sizeof(NoFila));
    if (novo == NULL) {
        printf("Erro ao alocar memória\n");
        return;
    }

    novo->enderecoNo = no;
    novo->proximo = NULL;

    if (fila->inicio == NULL) {
        fila->inicio = novo;
        fila->final = novo;
    }
    else {
        fila->final->proximo = novo;
        fila->final = novo;
    }
}

// Remove elementos da fila
No* desenfileirar(Fila *fila) {
    if (fila->inicio == NULL) {
        printf("Fila vazia!\n");
        return NULL;
    }
    else {
        NoFila* temp = fila->inicio;
        No* endereco = temp->enderecoNo;
        fila->inicio = fila->inicio->proximo;
        free(temp);
        return endereco;
    }
}

// Desaloca memória da fila
void liberarFila(Fila *fila) {   
    while (fila->inicio) {   
        desenfileirar(fila);
    }
    free(fila);
}

// Cria um novo nó
No* criar_no(int chave, bool eh_folha) {
    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo) {
        novoNo->chaves[0] = chave;
        novoNo->chaves[1] = 0;
        novoNo->chaves[2] = 0;
        novoNo->num_chaves = 1;
        novoNo->eh_folha = eh_folha;
        for (int i = 0; i < 4; i++) {
            novoNo->filhos[i] = NULL;
        }
    } else {
        printf("Erro ao alocar nó.\n");
    }
    return novoNo;
}

// Encontra o índice do filho onde o valor deve ser inserido
int encontrar_indice_filho(No* no, int valor) {
    if (valor < no->chaves[0]) return 0;
    if (no->num_chaves == 1 || valor < no->chaves[1]) return 1;
    return 2;
}

// Insere uma chave mantendo a ordem
void inserir_chave(No* no, int chave) {
    int i = no->num_chaves -1;
    while (i >= 0 && chave < no->chaves[i]) {
        no->chaves[i+1] = no->chaves[i];
        i--;
    }
    no->chaves[i+1] = chave;
    no->num_chaves++;
}

// Move os filhos mais à direita para abrir espaço para o novo filho
void inserir_filho(No* pai, No* filho, int indice) {
    for (int i = 3; i > indice; i--) {
        pai->filhos[i] = pai->filhos[i - 1];
    }
    pai->filhos[indice] = filho;
}

// Divide um filho cheio
void dividir_filho(No* pai, int subarvore_sucessora) {
    No* filho = pai->filhos[subarvore_sucessora];
    No* novo_no = criar_no(filho->chaves[2], filho->eh_folha);
    novo_no->num_chaves = 1;

    // Promove a chave do meio para o pai
    inserir_chave(pai, filho->chaves[1]);

    // Atualiza os filhos
    inserir_filho(pai, novo_no, subarvore_sucessora + 1);

    // Atualiza o filho original
    filho->num_chaves = 1;

    // Reorganiza os filhos
    if (!filho->eh_folha) {
        novo_no->filhos[0] = filho->filhos[2];
        novo_no->filhos[1] = filho->filhos[3];
        filho->filhos[2] = NULL;
        filho->filhos[3] = NULL;
    }
}

// Função principal de inserção
No* adicionar_no(No* no, int valor, bool* deve_dividir) {
    if (no->chaves[0] == valor || (no->num_chaves == 2 && no->chaves[1] == valor)) {
        printf("Valor já existente na árvore.\n");
        return no;
    }
    if (no->eh_folha) {
        inserir_chave(no, valor);
        *deve_dividir = (no->num_chaves > 2);
    } else {
        int subarvore_sucessora = encontrar_indice_filho(no, valor);
        bool divisao_filho = false;
        No* filho = no->filhos[subarvore_sucessora];

        filho = adicionar_no(filho, valor, &divisao_filho);
        no->filhos[subarvore_sucessora] = filho;

        if (divisao_filho) {
            dividir_filho(no, subarvore_sucessora);
            *deve_dividir = (no->num_chaves > 2);
        }
    }
    return no;
}

// Divide a raiz quando necessário
No* dividir_raiz(No* raiz) {
    No* nova_raiz = criar_no(raiz->chaves[1], false);
    No* esquerda = criar_no(raiz->chaves[0], raiz->eh_folha);
    No* direita = criar_no(raiz->chaves[2], raiz->eh_folha);

    esquerda->filhos[0] = raiz->filhos[0];
    esquerda->filhos[1] = raiz->filhos[1];
    direita->filhos[0] = raiz->filhos[2];
    direita->filhos[1] = raiz->filhos[3];

    nova_raiz->filhos[0] = esquerda;
    nova_raiz->filhos[1] = direita;

    free(raiz);
    return nova_raiz;
}

// Função de inserção geral
No* inserir(No* raiz, int valor) {
    if (!raiz) {
        return criar_no(valor, true);
    } else {
        bool deve_dividir = false;
        raiz = adicionar_no(raiz, valor, &deve_dividir);

        if (deve_dividir) {
            raiz = dividir_raiz(raiz);
        }
    }
    return raiz;
}

int altura(No *raiz) {
    if (!raiz) {
        return 0;
    }

    if (raiz->eh_folha) {
        return 1;
    }

    return altura(raiz->filhos[0]) + 1;
}

void em_ordem(No* raiz) {
    if (raiz) {
        em_ordem(raiz->filhos[0]);
        printf("%d ", raiz->chaves[0]);
        em_ordem(raiz->filhos[1]);
        if (raiz->num_chaves == 2) {
            printf("%d ", raiz->chaves[1]);
            em_ordem(raiz->filhos[2]);
        }
    }
}

void em_nivel(No *raiz) {
    if (!raiz) {
        printf("Árvore vazia!\n");
        return;
    }

    Fila *fila = malloc(sizeof(Fila));
    iniciarFila(fila);

    enfileirar(fila, raiz);

    while (fila->inicio) {
        int nosNoNivel = 0;
        NoFila *temp = fila->inicio;

        while (temp) {
            nosNoNivel++;
            temp = temp->proximo;
        }

        for (int i = 0; i < nosNoNivel; i++) {
            No *atual = desenfileirar(fila);

            printf("[%d", atual->chaves[0]);
            if (atual->num_chaves == 2) {
                printf(", %d", atual->chaves[1]);
            }
            printf("] ");

            if (atual->filhos[0]) {
                enfileirar(fila, atual->filhos[0]);
            }
            if (atual->filhos[1]) {
                enfileirar(fila, atual->filhos[1]);
            }
            if (atual->filhos[2]) {
                enfileirar(fila, atual->filhos[2]);
            }
        }

        printf("\n");
    }

    liberarFila(fila);
}

bool buscar(No *raiz, int valor) {
    if (!raiz) {
        return false;
    }

    if (raiz->num_chaves == 1) {
        if (valor < raiz->chaves[0]) {
            return buscar(raiz->filhos[0], valor);
        } else if (valor > raiz->chaves[0]) {  
            return buscar(raiz->filhos[1], valor);
        } 
        else {
            return true;
        }
    } 
    else {
        if (valor < raiz->chaves[0]) {
            return buscar(raiz->filhos[0], valor);
        } else if (valor > raiz->chaves[0] && valor < raiz->chaves[1]) {
            return buscar(raiz->filhos[1], valor);
        } else if (valor > raiz->chaves[1]) {
            return buscar(raiz->filhos[2], valor);
        } else {
            return true;
        }
    }
}

void remover_chave(No* no, int valor){
    if (no->num_chaves == 1) {
        no->chaves[0] = 0;
        no->num_chaves = 0;
    } else {
        if (no->chaves[0] == valor) {
            no->chaves[0] = no->chaves[1];
        }
        no->chaves[1] = 0;
        no->num_chaves = 1;
    }
}

No* redistribuicao_no_simples(No* pai) {
    No* esquerda = pai->filhos[0];
    No* direita = pai->filhos[1];

    if (esquerda->num_chaves == 0) {
        inserir_chave(esquerda, pai->chaves[0]);
        pai->chaves[0] = direita->chaves[0];
        remover_chave(direita, direita->chaves[0]);

        if (!esquerda->eh_folha) {
            inserir_filho(esquerda, direita->filhos[0], 1);
            direita->filhos[0] = direita->filhos[1];
            direita->filhos[1] = direita->filhos[2];
            direita->filhos[2] = NULL;
        }
    }
    else {
        inserir_chave(direita, pai->chaves[0]);
        pai->chaves[0] = esquerda->chaves[1];
        remover_chave(esquerda, esquerda->chaves[1]);

        if (!direita->eh_folha) {
            inserir_filho(direita, esquerda->filhos[2], 0);
            esquerda->filhos[2] = NULL;
        }
    }
   
    return pai;
}

No* fusao_no_simples(No* pai, int indice_irmao, int subarvore_sucessora){
    No* irmao = pai->filhos[indice_irmao];
    No* filho_vazio = pai->filhos[subarvore_sucessora];

    inserir_chave(irmao, pai->chaves[0]);
    remover_chave(pai, pai->chaves[0]);

    if (indice_irmao == 1) {
        pai->filhos[0] = irmao;
    }

    if (!irmao->eh_folha) {   
        if (indice_irmao == 1) {
            inserir_filho(irmao, filho_vazio->filhos[0], 0);
        } else {
            inserir_filho(irmao, filho_vazio->filhos[0], 2);
        }
    }
        
    for (int i = 1; i < 3; i++) {
        pai->filhos[i] = NULL;
    }
    
    pai->num_chaves = 0;

    return pai;
}

No* obter_sucessor(No* no, int chave_interna) {
    if (no->eh_folha) {
        return no;
    }
    int indice_filho = (chave_interna == 0) ? 1 : 2;

    No* atual = no->filhos[indice_filho];
    while (!atual->eh_folha) {
        atual = atual->filhos[0];
    }
    
    return atual;
}

No* redistribuicao_no_duplo(No *pai, int indice_filho) {
    int indice_irmao = (indice_filho == 1) ? 0 : 1;
    No* filho = pai->filhos[indice_filho];
    No* irmao = pai->filhos[indice_irmao];

    switch (indice_filho) {
    case 0:
        inserir_chave(filho, pai->chaves[0]);
        pai->chaves[0] = irmao->chaves[0];
        remover_chave(irmao, irmao->chaves[0]);
        break;
    case 1:
        inserir_chave(filho, pai->chaves[0]);
        pai->chaves[0] = irmao->chaves[1];
        remover_chave(irmao, irmao->chaves[1]);
        break;
    case 2:
        inserir_chave(filho, pai->chaves[1]);
        pai->chaves[1] = irmao->chaves[1];
        remover_chave(irmao, irmao->chaves[1]);
        break;
    default:
        break;
    }
    return pai;
}

No* fusao_no_duplo(No *pai, int indice_filho) {
    switch (indice_filho) 
    {
    case 0: 
        inserir_chave(pai->filhos[0], pai->chaves[0]);
        inserir_chave(pai->filhos[0], pai->filhos[1]->chaves[0]);
        remover_chave(pai, pai->chaves[0]);

        if (!pai->filhos[0]->eh_folha)
            inserir_filho(pai->filhos[1], pai->filhos[0]->filhos[0], 0);

        pai->filhos[1] = pai->filhos[2];
        pai->filhos[2] = NULL;
        break;
    case 1:
        inserir_chave(pai->filhos[0], pai->chaves[0]);
        remover_chave(pai, pai->chaves[0]);

        if (!pai->filhos[1]->eh_folha)
           inserir_filho(pai->filhos[0], pai->filhos[1]->filhos[0], 2);

        pai->filhos[1] = pai->filhos[2];
        pai->filhos[2] = NULL;
        break;
    case 2:
        inserir_chave(pai->filhos[1], pai->chaves[1]);
        remover_chave(pai, pai->chaves[1]);

        if (!pai->filhos[2]->eh_folha)
            inserir_filho(pai->filhos[1], pai->filhos[2]->filhos[0], 2);

        pai->filhos[2] = NULL;
        break;
    default:
        break;
    }
    return pai;
}

void rebalancear(No* no, int indice_filho) {
    if (no->num_chaves == 1) {
        int indice_irmao = (indice_filho == 0) ? 1 : 0;
        if (no->filhos[indice_irmao]->num_chaves == 2) {
            no = redistribuicao_no_simples(no);
        } else {
            no = fusao_no_simples(no, indice_irmao, indice_filho);
        }
    } else {
        int indice_irmao = (indice_filho == 1) ? 0 : 1;
        if (no->filhos[indice_irmao]->num_chaves == 2) {
            no = redistribuicao_no_duplo(no, indice_filho);
        } else {
            no = fusao_no_duplo(no, indice_filho);
        }
    }
}

No* deletar_item(No* no, int valor) {
    if (!no) {
        printf("Valor não encontrado!\n");
        return no;
    }

    int chave_interna = -1;
    if (valor == no->chaves[0]) {
        chave_interna = 0;
    } else if (no->num_chaves == 2 && valor == no->chaves[1]) {
        chave_interna = 1;
    }

    if (chave_interna != -1) {
        if (no->eh_folha) {
            remover_chave(no, valor);
        } else {
            No* sucessor = obter_sucessor(no, chave_interna);
            
            if (!sucessor) {
                printf("Erro: sucessor não encontrado\n");
                return no;
            }

           int temp = no->chaves[chave_interna];
           no->chaves[chave_interna] = sucessor->chaves[0];
           sucessor->chaves[0] = temp;

           int indice_filho = (chave_interna == 0) ? 1 : 2;
           if (no->num_chaves == 1) chave_interna = 1;

           No* filho = no->filhos[indice_filho];
           filho = deletar_item(no->filhos[indice_filho], sucessor->chaves[0]);

            if (filho) {
                if (filho->num_chaves == 0) {
                    rebalancear(no, indice_filho);
                }
            } 
        }
    } else {
        int indice_filho = encontrar_indice_filho(no, valor);
        No* filho = no->filhos[indice_filho];

        filho = deletar_item(filho, valor);

        if (filho) {
            if (filho->num_chaves == 0) {
                rebalancear(no, indice_filho);
            }
        }
    }

    return no;
}

No* remover_valor(No* no, int valor) {
    if (!no) {
        printf("Árvore vazia!\n");
        return NULL;
    }
    
    no = deletar_item(no, valor);

    if (no->num_chaves == 0) {
        if (no->filhos[0]) {
            no = no->filhos[0];
        } else {
          no = NULL;  
        }
    } 
    return no;
}

void insercao(int elementos[], int tam) {
    No* raiz = NULL;
    for (int i = 0; i < tam; i++) {  
        printf("Inserção de %d: \n", elementos[i]);
        raiz = inserir(raiz, elementos[i]);
        em_nivel(raiz);
        printf("-------------\n");
    }
}

void remocao(int elementos[], int tam) {
    No* raiz = NULL;

    for (int i = 0; i < tam; i++) {   
        raiz = inserir(raiz, elementos[i]);
    }
    
    printf("Original: \n");
    em_nivel(raiz);
    printf("-------------\n");
    for (int i = 0; i < tam; i++) {   
        printf("Remoção de %d: \n", elementos[i]);
        raiz = remover_valor(raiz, elementos[i]);
        em_nivel(raiz);
        printf("-------------\n");
    }
}

void busca(int elementos[], int tam) {
    No* raiz = NULL;

    for (int i = 0; i < tam; i++) {   
        raiz = inserir(raiz, elementos[i]);
    }
    
    for (int i = 0; i < tam; i++) {   
        if (buscar(raiz, elementos[i])){
            printf("Elemento %d encontrado!\n", elementos[i]);
        } else {
            printf("Elemento %d não encontrado.\n", elementos[i]);
        }
    }
}

void desenharNo(TelaVisualizacao *tela, No *no, int linha, int coluna) {
    if (!no) return;

    char noStr[20];
    if (no->num_chaves == 2) {
        sprintf(noStr, "[%d|%d]", no->chaves[0], no->chaves[1]);
    } else {
        sprintf(noStr, "[%d]", no->chaves[0]);
    }

    int len = strlen(noStr);
    int start = coluna - len / 2;
    for (int i = 0; i < len; i++) {
        if (start + i >= 0 && start + i < tela->largura) {
            tela->tela[linha][start + i] = noStr[i];
        }
    }
}

void desenharConexoes(TelaVisualizacao *tela, int linhaPai, int colunaPai,
                      int linhaFilho, int colunaFilho, bool ehMeio, bool ehNoPaiDuplo) {
    if (ehMeio) {
        int ajuste = ehNoPaiDuplo ? 0 : 1;
        for (int i = 1; i < linhaFilho - linhaPai; i++) {
            tela->tela[linhaPai + i][colunaPai + ajuste] = '|';
        }
    } else {
        int distancia = abs(colunaFilho - colunaPai);
        int direcao = (colunaFilho < colunaPai) ? -1 : 1;
        char simbolo = (direcao < 0) ? '/' : '\\';

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

void desenharArvoreRecursivo(TelaVisualizacao *tela, No *no, int nivel, int coluna) {
    if (!no) return;

    int linha = nivel * 3;
    bool ehNoDuplo = no->num_chaves == 2;
    desenharNo(tela, no, linha, coluna);

    if (!no->eh_folha) {
        int espacamento = 20 / (nivel + 1);

        if (!ehNoDuplo) {
            espacamento = (espacamento * 4) / 5;
        }

        int colunaEsq = coluna - espacamento;
        int colunaDir = coluna + espacamento;

        desenharArvoreRecursivo(tela, no->filhos[0], nivel + 1, colunaEsq);
        desenharConexoes(tela, linha, coluna, linha + 3, colunaEsq, false, ehNoDuplo);

        if (ehNoDuplo) {
            desenharArvoreRecursivo(tela, no->filhos[1], nivel + 1, coluna);
            desenharConexoes(tela, linha, coluna, linha + 3, coluna, true, ehNoDuplo);

            desenharArvoreRecursivo(tela, no->filhos[2], nivel + 1, colunaDir);
            desenharConexoes(tela, linha, coluna, linha + 3, colunaDir, false, ehNoDuplo);
        } else {
            desenharArvoreRecursivo(tela, no->filhos[1], nivel + 1, colunaDir);
            desenharConexoes(tela, linha, coluna, linha + 3, colunaDir, false, ehNoDuplo);
        }
    }
}

void imprimirArvore(No *raiz) {
    if (!raiz) {
        printf("\n=== Árvore 2-3 Vazia ===\n");
        return;
    }

    TelaVisualizacao *tela = malloc(sizeof(TelaVisualizacao));
    tela->altura = ALTURA_TELA;
    tela->largura = LARGURA_TELA;

    tela->tela = malloc(ALTURA_TELA * sizeof(char *));
    for (int i = 0; i < ALTURA_TELA; i++) {
        tela->tela[i] = malloc(LARGURA_TELA * sizeof(char));
        memset(tela->tela[i], ' ', LARGURA_TELA);
    }

    printf("\n=== Árvore 2-3 ===\n\n");

    desenharArvoreRecursivo(tela, raiz, 0, LARGURA_TELA / 2);

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

    for (int i = 0; i < tela->altura; i++) {
        free(tela->tela[i]);
    }
    free(tela->tela);
    free(tela);
}

void menu() {
    int opcao, valor;

    No* raiz = NULL;

    do {
        printf("------------\n");
        em_nivel(raiz);
        printf("------------\n\n");
        printf("0 - Sair\n");
        printf("1 - Inserir\n");
        printf("2 - Imprimir em ordem \n");
        printf("3 - Checar altura\n");
        printf("4 - Buscar Valor\n");
        printf("5 - Remover Valor\n");
        printf("6 - Desenhar Árvore\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        printf("------------\n");

        switch (opcao) {
        case 0:
            printf("Saindo..\n");
            break;
        case 1:
            printf("Digite um valor para inserir: ");
            scanf("%d", &valor);
            getc(stdin);
            raiz = inserir(raiz, valor);
            break;
        case 2:
            printf("Em ordem: ");
            em_ordem(raiz);
            printf("\n");
            break;
        case 3:
            printf("A altura da árvore é: %d\n", altura(raiz));
            break;
        case 4:
            printf("Digite um valor a ser procurado: ");
            scanf("%d", &valor);
            getc(stdin);

            if (buscar(raiz, valor)) {
                printf("Elemento %d encontrado!\n", valor);
            } else {
                printf("Elemento %d não encontrado.\n", valor);
            }
            break;
        case 5:
            printf("Digite um valor a ser removido: ");
            scanf("%d", &valor);
            getc(stdin);
            raiz = remover_valor(raiz, valor);
            break;
        case 6:
            imprimirArvore(raiz);
            break;
        default:
            printf("\nOpção não válida.\n");
            break;
        }

    } while (opcao != 0);
}

int main() {
    int elementos[] = {10, 20, 30, 40, 50, 60, 70, 80, 90};
    int tam = sizeof(elementos)/sizeof(int);

    menu();
    
    return 0;
}