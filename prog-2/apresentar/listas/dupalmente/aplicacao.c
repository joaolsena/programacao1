#include <stdio.h>
#include <stdlib.h>

struct No {
    int id; // ID do cliente
    struct No* prox;
    struct No* anterior;
};

// Função para criar um nó
struct No* criarNo(int id) {
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    novoNo->id = id;
    novoNo->prox = NULL;
    novoNo->anterior = NULL;
    return novoNo;
}

// Adicionar cliente no fim da fila
void adicionarCliente(struct No** head, int id) {
    struct No* novoNo = criarNo(id);
    if (*head == NULL) {
        *head = novoNo;
    } else {
        struct No* temp = *head;
        while (temp->prox != NULL) {
            temp = temp->prox;
        }
        temp->prox = novoNo;
        novoNo->anterior = temp;
    }
    printf("Cliente %d adicionado à fila.\n", id);
}

// Remover cliente no início da fila
void atenderCliente(struct No** head) {
    if (*head == NULL) {
        printf("Nenhum cliente na fila!\n");
        return;
    }
    struct No* temp = *head;
    printf("Atendendo cliente ID: %d\n", temp->id);
    *head = temp->prox;
    if (*head != NULL) {
        (*head)->anterior = NULL;
    }
    free(temp);
}

// Imprimir a fila de clientes
void imprimirFila(struct No* head) {
    if (head == NULL) {
        printf("Fila vazia!\n");
        return;
    }
    printf("Fila de clientes: ");
    struct No* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->id);
        temp = temp->prox;
    }
    printf("\n");
}

int main() {
    struct No* fila = NULL;
    int opcao, id;

    do {
        printf("\n--- Sistema de Gerenciamento de Fila ---\n");
        printf("1. Adicionar cliente à fila\n");
        printf("2. Atender cliente\n");
        printf("3. Mostrar fila\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o ID do cliente: ");
                scanf("%d", &id);
                adicionarCliente(&fila, id);
                break;
            case 2:
                atenderCliente(&fila);
                break;
            case 3:
                imprimirFila(fila);
                break;
            case 4:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 4);

    // Liberar memória ao final
    while (fila != NULL) {
        atenderCliente(&fila);
    }

    return 0;
}
