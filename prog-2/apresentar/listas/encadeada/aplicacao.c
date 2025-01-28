#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura do nó
struct No {
    char tarefa[100];  // Descrição da tarefa
    struct No* prox;   // Ponteiro para o próximo nó
};

// Função para criar um novo nó
struct No* criarNo(char* descricao) {
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    strcpy(novoNo->tarefa, descricao); // Copia a descrição para o nó
    novoNo->prox = NULL;
    return novoNo;
}

// Função para inserir uma tarefa no final da lista
void inserirTarefa(struct No** inicio, char* descricao) {
    struct No* novoNo = criarNo(descricao);

    if (*inicio == NULL) { // Lista vazia
        *inicio = novoNo;
    } else {
        struct No* temp = *inicio;
        while (temp->prox != NULL) { // Percorre até o último nó
            temp = temp->prox;
        }
        temp->prox = novoNo; // Último nó aponta para o novo nó
    }
    printf("Tarefa adicionada: %s\n", descricao);
}

// Função para remover a primeira tarefa
void removerTarefa(struct No** inicio) {
    if (*inicio == NULL) {
        printf("A lista está vazia. Nenhuma tarefa para remover.\n");
        return;
    }

    struct No* temp = *inicio; // Nó a ser removido
    *inicio = (*inicio)->prox; // Atualiza o início da lista
    printf("Tarefa removida: %s\n", temp->tarefa);
    free(temp); // Libera a memória
}

// Função para imprimir a lista de tarefas
void imprimirTarefas(struct No* inicio) {
    if (inicio == NULL) {
        printf("Nenhuma tarefa na lista.\n");
        return;
    }

    printf("\nLista de Tarefas:\n");
    struct No* temp = inicio;
    while (temp != NULL) {
        printf("- %s\n", temp->tarefa);
        temp = temp->prox;
    }
}

int main() {
    struct No* listaDeTarefas = NULL; // Inicializa a lista vazia
    int opcao;
    char descricao[100];

    do {
        printf("\n--- Gerenciador de Tarefas ---\n");
        printf("1. Adicionar tarefa\n");
        printf("2. Remover tarefa\n");
        printf("3. Mostrar lista de tarefas\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Consome o '\n' deixado pelo scanf

        switch (opcao) {
            case 1:
                printf("Digite a descrição da tarefa: ");
                fgets(descricao, 100, stdin);
                descricao[strcspn(descricao, "\n")] = '\0'; // Remove o '\n'
                inserirTarefa(&listaDeTarefas, descricao);
                break;
            case 2:
                removerTarefa(&listaDeTarefas);
                break;
            case 3:
                imprimirTarefas(listaDeTarefas);
                break;
            case 4:
                printf("Saindo do gerenciador de tarefas...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 4);

    // Libera a memória ao final do programa
    while (listaDeTarefas != NULL) {
        removerTarefa(&listaDeTarefas);
    }

    return 0;
}
