#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó
struct No {
    int dado;          // Dado armazenado no nó
    struct No* prox;   // Ponteiro para o próximo nó
};

// Função para criar um novo nó
struct No* criarNo(int valor) {
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    novoNo->dado = valor;
    novoNo->prox = NULL;
    return novoNo;
}

// Função para inserir no início da lista
void inserirInicio(struct No** inicio, int valor) {
    struct No* novoNo = criarNo(valor);
    novoNo->prox = *inicio; // Novo nó aponta para o início atual
    *inicio = novoNo;       // Atualiza o início da lista
}

// Função para inserir no fim da lista
void inserirFim(struct No** inicio, int valor) {
    struct No* novoNo = criarNo(valor);

    if (*inicio == NULL) { // Lista vazia
        *inicio = novoNo;
    } else {
        struct No* temp = *inicio;
        while (temp->prox != NULL) { // Percorre até o último nó
            temp = temp->prox;
        }
        temp->prox = novoNo; // Último nó aponta para o novo nó
    }
}

// Função para remover no início da lista
void removerInicio(struct No** inicio) {
    if (*inicio == NULL) return; // Lista vazia

    struct No* temp = *inicio; // Nó a ser removido
    *inicio = (*inicio)->prox; // Atualiza o início da lista
    free(temp); // Libera a memória
}

// Função para remover no fim da lista
void removerFim(struct No** inicio) {
    if (*inicio == NULL) return; // Lista vazia

    struct No* temp = *inicio;
    if (temp->prox == NULL) { // Lista com apenas um nó
        *inicio = NULL;
        free(temp);
        return;
    }

    // Percorre até o penúltimo nó
    while (temp->prox->prox != NULL) {
        temp = temp->prox;
    }
    free(temp->prox); // Libera o último nó
    temp->prox = NULL; // Penúltimo nó aponta para NULL
}

// Função para inserir no meio da lista (após um nó específico)
void inserirMeio(struct No* noAnterior, int valor) {
    if (noAnterior == NULL) return; // Verifica se o nó anterior é válido

    struct No* novoNo = criarNo(valor);
    novoNo->prox = noAnterior->prox; // Novo nó aponta para o próximo do anterior
    noAnterior->prox = novoNo;       // Anterior aponta para o novo nó
}

// Função para remover no meio da lista (nó após um nó específico)
void removerMeio(struct No* noAnterior) {
    if (noAnterior == NULL || noAnterior->prox == NULL) return; // Verifica se é válido

    struct No* noRemovido = noAnterior->prox; // Nó a ser removido
    noAnterior->prox = noRemovido->prox;      // Anterior aponta para o próximo do removido
    free(noRemovido);                         // Libera a memória
}

// Função para imprimir a lista
void imprimirLista(struct No* inicio) {
    struct No* temp = inicio;
    while (temp != NULL) {
        printf("%d -> ", temp->dado);
        temp = temp->prox;
    }
    printf("NULL\n");
}

int main() {
    struct No* inicio = NULL; // Inicializa a lista vazia

    // Adicionando elementos
    inserirInicio(&inicio, 10); // Lista: 10 -> NULL
    inserirFim(&inicio, 20);    // Lista: 10 -> 20 -> NULL
    inserirInicio(&inicio, 5);  // Lista: 5 -> 10 -> 20 -> NULL
    inserirFim(&inicio, 30);    // Lista: 5 -> 10 -> 20 -> 30 -> NULL

    printf("Lista após adições:\n");
    imprimirLista(inicio);

    // Adicionando no meio (15 após o 10)
    struct No* temp = inicio;
    while (temp != NULL && temp->dado != 10) {
        temp = temp->prox;
    }
    if (temp != NULL) {
        inserirMeio(temp, 15); // Lista: 5 -> 10 -> 15 -> 20 -> 30 -> NULL
    }

    printf("\nLista após adicionar 15 no meio:\n");
    imprimirLista(inicio);

    // Removendo no início
    removerInicio(&inicio); // Lista: 10 -> 15 -> 20 -> 30 -> NULL
    printf("\nLista após remover no início:\n");
    imprimirLista(inicio);

    // Removendo no fim
    removerFim(&inicio); // Lista: 10 -> 15 -> 20 -> NULL
    printf("\nLista após remover no fim:\n");
    imprimirLista(inicio);

    // Removendo no meio (15)
    temp = inicio;
    while (temp != NULL && temp->dado != 10) {
        temp = temp->prox;
    }
    if (temp != NULL) {
        removerMeio(temp); // Lista: 10 -> 20 -> NULL
    }

    printf("\nLista após remover 15 no meio:\n");
    imprimirLista(inicio);

    return 0;
}