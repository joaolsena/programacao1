#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó
struct No {
    int dado;           // Valor armazenado no nó
    struct No* prox;    // Ponteiro para o próximo nó
    struct No* ant;     // Ponteiro para o nó anterior
};

// Função para criar um novo nó
struct No* criarNo(int valor) {
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    novoNo->dado = valor;
    novoNo->prox = NULL;
    novoNo->ant = NULL;
    return novoNo;
}

// Função para inserir no final da lista
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
        novoNo->ant = temp; // Novo nó aponta para o anterior
    }
}

// Função para buscar um elemento na lista (bidirecional)
struct No* buscarBidirecional(struct No* inicio, int valor) {
    if (inicio == NULL) return NULL; // Lista vazia

    struct No* inicioPtr = inicio;  // Ponteiro para percorrer do início
    struct No* fimPtr = inicio;     // Ponteiro para percorrer do fim

    // Localiza o último nó
    while (fimPtr->prox != NULL) {
        fimPtr = fimPtr->prox;
    }

    // Percorre simultaneamente do início e do fim
    while (inicioPtr != fimPtr && fimPtr->prox != inicioPtr) {
        if (inicioPtr->dado == valor) return inicioPtr; // Encontrado no início
        if (fimPtr->dado == valor) return fimPtr;       // Encontrado no fim

        inicioPtr = inicioPtr->prox; // Avança a partir do início
        fimPtr = fimPtr->ant;        // Retrocede a partir do fim
    }

    // Verifica se o valor está no nó do meio (caso os ponteiros se encontrem)
    if (inicioPtr->dado == valor) return inicioPtr;

    return NULL; // Valor não encontrado
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
    struct No* lista = NULL;

    // Inserindo valores na lista
    inserirFim(&lista, 10);
    inserirFim(&lista, 20);
    inserirFim(&lista, 30);
    inserirFim(&lista, 40);
    inserirFim(&lista, 50);

    printf("Lista atual:\n");
    imprimirLista(lista);

    // Buscando um valor
    int valorBuscado;
    printf("\nDigite um valor para buscar na lista: ");
    scanf("%d", &valorBuscado);

    struct No* encontrado = buscarBidirecional(lista, valorBuscado);
    if (encontrado != NULL) {
        printf("Valor %d encontrado no nó com endereço %p\n", encontrado->dado, (void*)encontrado);
    } else {
        printf("Valor %d não encontrado na lista.\n", valorBuscado);
    }

    return 0;
}
