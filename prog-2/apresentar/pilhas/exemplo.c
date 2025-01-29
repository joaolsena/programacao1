#include <stdio.h>
#include <stdlib.h>

// Estrutura para um nó da pilha
typedef struct Node {
    int dado;
    struct Node *proximo;
} Node;

// Função para criar um novo nó
Node* criarNo(int dado) {
    Node *novoNo = (Node *)malloc(sizeof(Node));
    if (novoNo == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    novoNo->dado = dado;
    novoNo->proximo = NULL;
    return novoNo;
}

// Função para verificar se a pilha está vazia
int estaVazia(Node *topo) {
    return topo == NULL;
}

// Função para empilhar um elemento
void empilhar(Node **topo, int dado) {
    Node *novoNo = criarNo(dado);
    novoNo->proximo = *topo;
    *topo = novoNo;
    printf("%d empilhado na pilha.\n", dado);
}

// Função para desempilhar um elemento
int desempilhar(Node **topo) {
    if (estaVazia(*topo)) {
        printf("A pilha está vazia. Não há nada para desempilhar.\n");
        return -1;
    }
    Node *temp = *topo;
    int dadoDesempilhado = temp->dado;
    *topo = (*topo)->proximo;
    free(temp);
    printf("%d desempilhado da pilha.\n", dadoDesempilhado);
    return dadoDesempilhado;
}

// Função para imprimir a pilha
void imprimirPilha(Node *topo) {
    if (estaVazia(topo)) {
        printf("A pilha está vazia.\n");
        return;
    }
    printf("Elementos da pilha: ");
    Node *atual = topo;
    while (atual != NULL) {
        printf("%d ", atual->dado);
        atual = atual->proximo;
    }
    printf("\n");
}

// Função para exibir o elemento do topo da pilha
void exibirTopo(Node *topo) {
    if (estaVazia(topo)) {
        printf("A pilha está vazia.\n");
    } else {
        printf("Topo da pilha: %d\n", topo->dado);
    }
}

int main() {
    Node *pilha = NULL; // Inicialização da pilha

    int escolha, valor;

    do {
        printf("\nMenu:\n");
        printf("1. Empilhar\n");
        printf("2. Desempilhar\n");
        printf("3. Imprimir pilha\n");
        printf("4. Exibir topo da pilha\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                printf("Digite o valor para empilhar: ");
                scanf("%d", &valor);
                empilhar(&pilha, valor);
                break;
            case 2:
                desempilhar(&pilha);
                break;
            case 3:
                imprimirPilha(pilha);
                break;
            case 4:
                exibirTopo(pilha);
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (escolha != 5);

    // Libera a memória alocada
    while (!estaVazia(pilha)) {
        desempilhar(&pilha);
    }

    return 0;
}