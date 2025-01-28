#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó
struct No {
    int dado;
    struct No* prox;
    struct No* anterior;
};

// Função para criar um novo nó
struct No *criarNo(int valor) {
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    novoNo->dado = valor;
    novoNo->prox = NULL;
    novoNo->anterior = NULL;
    return novoNo;
}

// Função para adicionar no início
void adicionarInicio(struct No** head, int valor) {
    struct No* novoNo = criarNo(valor);

    if (*head == NULL) { // Lista vazia
        *head = novoNo;
    } else {
        novoNo->prox = *head;
        (*head)->anterior = novoNo;
        *head = novoNo;
    }
}

// Função para adicionar no fim
void adicionarFim(struct No** head, int valor) {
    struct No* novoNo = criarNo(valor);

    if (*head == NULL) { // Lista vazia
        *head = novoNo;
    } else {
        struct No* temp = *head;
        while (temp->prox != NULL) { // Encontra o último nó
            temp = temp->prox;
        }
        temp->prox = novoNo;
        novoNo->anterior = temp;
    }
}

// Função para remover no início
void removerInicio(struct No** head) {
    if (*head == NULL) return; // Lista vazia

    struct No* temp = *head;
    *head = (*head)->prox; // Atualiza o início da lista
    if (*head != NULL) {
        (*head)->anterior = NULL; // O anterior do novo início é NULL
    }
    free(temp); // Libera a memória
}

// Função para remover no fim
void removerFim(struct No** head) {
    if (*head == NULL) return; // Lista vazia

    struct No* temp = *head;
    if (temp->prox == NULL) { // Lista com apenas um nó
        *head = NULL;
        free(temp);
        return;
    }

    while (temp->prox != NULL) { // Encontra o último nó
        temp = temp->prox;
    }
    temp->anterior->prox = NULL; // O penúltimo nó aponta para NULL
    free(temp); // Libera a memória
}

// Função para adicionar no meio
void adicionarMeio(struct No* anterior, int valor) {
    if (anterior == NULL) return; // Verifica se o nó anterior é válido

    struct No* novoNo = criarNo(valor);
    novoNo->prox = anterior->prox;
    novoNo->anterior = anterior;
    if (anterior->prox != NULL) {
        anterior->prox->anterior = novoNo;
    }
    anterior->prox = novoNo;
}

// Função para remover no meio
void removerMeio(struct No* anterior) {
    if (anterior == NULL || anterior->prox == NULL) return; // Verifica se é válido

    struct No* noRemovido = anterior->prox;
    anterior->prox = noRemovido->prox;
    if (noRemovido->prox != NULL) {
        noRemovido->prox->anterior = anterior;
    }
    free(noRemovido);
}

// Função para imprimir a lista
void imprimirLista(struct No* head) {
    struct No* temp = head;
    while (temp != NULL) {
        printf("%d <-> ", temp->dado);
        temp = temp->prox;
    }
    printf("NULL\n");
}

int main() {
    struct No* head = NULL; // Inicializa a lista vazia

    // Adicionando elementos
    adicionarInicio(&head, 10); // Lista: 10 <-> NULL
    adicionarFim(&head, 20);    // Lista: 10 <-> 20 <-> NULL
    adicionarInicio(&head, 5);  // Lista: 5 <-> 10 <-> 20 <-> NULL
    adicionarFim(&head, 30);    // Lista: 5 <-> 10 <-> 20 <-> 30 <-> NULL

    printf("Lista:\n");
    imprimirLista(head);

    // Adicionando no meio (15 após o 10)
    struct No* temp = head;
    while (temp != NULL && temp->dado != 10) {
        temp = temp->prox;
    }
    if (temp != NULL) {
        adicionarMeio(temp, 15); // Lista: 5 <-> 10 <-> 15 <-> 20 <-> 30 <-> NULL
    }

    printf("\nLista após adicionar 15 no meio:\n");
    imprimirLista(head);

    // Removendo no início
    removerInicio(&head); // Lista: 10 <-> 15 <-> 20 <-> 30 <-> NULL
    printf("\nLista após remover no início:\n");
    imprimirLista(head);

    // Removendo no fim
    removerFim(&head); // Lista: 10 <-> 15 <-> 20 <-> NULL
    printf("\nLista após remover no fim:\n");
    imprimirLista(head);

    // Removendo no meio (15)
    temp = head;
    while (temp != NULL && temp->dado != 10) {
        temp = temp->prox;
    }
    if (temp != NULL) {
        removerMeio(temp); // Lista: 10 <-> 20 <-> NULL
    }

    printf("\nLista após remover 15 no meio:\n");
    imprimirLista(head);

    return 0;
}
