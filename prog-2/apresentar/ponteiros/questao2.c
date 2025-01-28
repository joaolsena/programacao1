#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

void insertAtEnd(Node** head, int value) {
    Node* newNode = createNode(value);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    printf("Valor %d inserido no final.\n", value);
}

void removeFromBeginning(Node** head) {
    if (*head == NULL) {
        printf("A lista está vazia! Nada para remover.\n");
        return;
    }
    Node* temp = *head;
    *head = (*head)->next;
    printf("Valor %d removido do início.\n", temp->data);
    free(temp);
}

void display(Node* head) {
    if (head == NULL) {
        printf("A lista está vazia!\n");
        return;
    }
    Node* temp = head;
    printf("Lista: ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void insertAtPosition(Node** head, int value, int position) {
    Node* newNode = createNode(value);
    if (position == 1) {
        newNode->next = *head;
        *head = newNode;
        printf("Valor %d inserido na posição %d.\n", value, position);
        return;
    }
    Node* temp = *head;
    int currentPosition = 1;
    while (temp != NULL && currentPosition < position - 1) {
        temp = temp->next;
        currentPosition++;
    }
    if (temp == NULL) {
        printf("Posição %d inválida! A lista tem menos nós.\n", position);
        free(newNode);
        return;
    }
    newNode->next = temp->next;
    temp->next = newNode;
    printf("Valor %d inserido na posição %d.\n", value, position);
}

void removeAtPosition(Node** head, int position) {
    if (*head == NULL) {
        printf("A lista está vazia! Nada para remover.\n");
        return;
    }
    if (position == 1) {
        Node* temp = *head;
        *head = (*head)->next;
        printf("Valor %d removido da posição %d.\n", temp->data, position);
        free(temp);
        return;
    }
    Node* temp = *head;
    int currentPosition = 1;
    while (temp != NULL && currentPosition < position - 1) {
        temp = temp->next;
        currentPosition++;
    }
    if (temp == NULL || temp->next == NULL) {
        printf("Posição %d inválida! A lista tem menos nós.\n", position);
        return;
    }
    Node* nodeToDelete = temp->next;
    temp->next = nodeToDelete->next;
    printf("Valor %d removido da posição %d.\n", nodeToDelete->data, position);
    free(nodeToDelete);
}

int main() {
    Node* head = NULL;
    int choice, value, position;

    printf("Insira 3 valores para a lista inicial:\n");
    for (int i = 0; i < 3; i++) {
        printf("Valor %d: ", i + 1);
        scanf("%d", &value);
        insertAtEnd(&head, value);
    }

    do {
        printf("\nMenu de Opções:\n");
        printf("1. Mostrar valores armazenados\n");
        printf("2. Adicionar valor ao final\n");
        printf("3. Remover valor do início\n");
        printf("4. Adicionar valor em posição específica\n");
        printf("5. Remover valor de posição específica\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                display(head);
                break;
            case 2:
                printf("Digite o valor a ser adicionado: ");
                scanf("%d", &value);
                insertAtEnd(&head, value);
                break;
            case 3:
                removeFromBeginning(&head);
                break;
            case 4:
                printf("Digite o valor a ser adicionado: ");
                scanf("%d", &value);
                printf("Digite a posição onde deseja adicionar: ");
                scanf("%d", &position);
                insertAtPosition(&head, value, position);
                break;
            case 5:
                printf("Digite a posição do valor a ser removido: ");
                scanf("%d", &position);
                removeAtPosition(&head, position);
                break;
            case 6:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (choice != 6);

    while (head != NULL) {
        removeFromBeginning(&head);
    }

    return 0;
}