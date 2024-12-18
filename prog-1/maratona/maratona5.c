#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_M 500
#define MAX_N 10000
#define HASH_SIZE 100003

typedef struct {
    int A, B, C, D;
} Plano;

typedef struct {
    int X, Y, Z;
} Planeta;

typedef struct Node {
    char key[MAX_M + 1]; // Chave como uma string de bits
    int count;
    struct Node* next;
} Node;

Node* hashTable[HASH_SIZE];

// Função de hash para string
unsigned long long hash_function(const char* key) {
    unsigned long long hash = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hash = (hash * 31 + key[i]) % HASH_SIZE;
    }
    return hash;
}

// Inserção ou incremento no hash map
void insert_or_increment(const char* key) {
    unsigned long long hashIndex = hash_function(key);
    Node* current = hashTable[hashIndex];

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            current->count++;
            return;
        }
        current = current->next;
    }

    // Se não encontrou, cria um novo nó
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->key, key);
    newNode->count = 1;
    newNode->next = hashTable[hashIndex];
    hashTable[hashIndex] = newNode;
}

// Busca no hash map para encontrar o máximo
int find_max_count() {
    int max_count = 0;
    for (int i = 0; i < HASH_SIZE; i++) {
        Node* current = hashTable[i];
        while (current != NULL) {
            if (current->count > max_count) {
                max_count = current->count;
            }
            current = current->next;
        }
    }
    return max_count;
}

int main() {
    int M, N;
    Plano planos[MAX_M];
    Planeta planetas[MAX_N];

    // Leitura dos valores de M (número de planos) e N (número de planetas)
    scanf("%d %d", &M, &N);

    // Leitura dos planos
    for (int i = 0; i < M; i++) {
        scanf("%d %d %d %d", &planos[i].A, &planos[i].B, &planos[i].C, &planos[i].D);
    }

    // Leitura dos planetas
    for (int i = 0; i < N; i++) {
        scanf("%d %d %d", &planetas[i].X, &planetas[i].Y, &planetas[i].Z);
    }

    // Processamento dos planetas e contagem nas regiões
    for (int i = 0; i < N; i++) {
        char chave_regiao[MAX_M + 1];
        memset(chave_regiao, 0, sizeof(chave_regiao));

        for (int j = 0; j < M; j++) {
            int S = planos[j].A * planetas[i].X + planos[j].B * planetas[i].Y +
                    planos[j].C * planetas[i].Z - planos[j].D;

            chave_regiao[j] = (S > 0) ? '1' : '0';
        }
        chave_regiao[M] = '\0'; // Finaliza a string

        insert_or_increment(chave_regiao);
    }

    // Encontrando o máximo número de planetas em uma região
    int max_planetas = find_max_count();
    printf("%d\n", max_planetas);

    return 0;
}
