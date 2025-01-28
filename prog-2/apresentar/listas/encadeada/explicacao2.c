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
    }
}

// Função para buscar um elemento na lista
struct No* buscarElemento(struct No* inicio, int valor) {
    struct No* temp = inicio;
    while (temp != NULL) { // Percorre a lista até o final
        if (temp->dado == valor) { // Se encontrar o valor
            return temp;           // Retorna o ponteiro para o nó
        }
        temp = temp->prox; // Avança para o próximo nó
    }
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

    printf("Lista atual:\n");
    imprimirLista(lista);

    // Buscando um elemento
    int valorBuscado;
    printf("Digite um valor para buscar na lista: ");
    scanf("%d", &valorBuscado);

    struct No* encontrado = buscarElemento(lista, valorBuscado);
    if (encontrado != NULL) {
        printf("Valor %d encontrado no nó com endereço %p\n", encontrado->dado, (void*)encontrado);
    } else {
        printf("Valor %d não encontrado na lista.\n", valorBuscado);
    }

    return 0;
}
