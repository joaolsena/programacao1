#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Estrutura do nó da Trie
typedef struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;
} TrieNode;

// Cria um novo nó da Trie
TrieNode* createNode() {
    TrieNode* newNode = (TrieNode*)malloc(sizeof(TrieNode));
    if (newNode) {
        newNode->isEndOfWord = false;
        for (int i = 0; i < ALPHABET_SIZE; i++)
            newNode->children[i] = NULL;
    }
    return newNode;
}

// Insere uma palavra na Trie
void insert(TrieNode* root, const char* word) {
    TrieNode* node = root;
    while (*word) {
        int index = *word - 'a';
        if (!node->children[index])
            node->children[index] = createNode();
        node = node->children[index];
        word++;
    }
    node->isEndOfWord = true;
}

// Busca uma palavra na Trie
bool search(TrieNode* root, const char* word) {
    TrieNode* node = root;
    while (*word) {
        int index = *word - 'a';
        if (!node->children[index])
            return false;
        node = node->children[index];
        word++;
    }
    return node->isEndOfWord;
}

// Função auxiliar para verificar se um nó tem filhos
bool hasChildren(TrieNode* node) {
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (node->children[i])
            return true;
    return false;
}

// Remove uma palavra da Trie
bool removeWord(TrieNode* root, const char* word, int depth) {
    if (!root)
        return false;

    if (*word) {
        int index = *word - 'a';
        if (root->children[index] &&
            removeWord(root->children[index], word + 1, depth + 1) &&
            !root->isEndOfWord) {
            if (!hasChildren(root->children[index])) {
                free(root->children[index]);
                root->children[index] = NULL;
                return !hasChildren(root);
            }
        }
    } else if (root->isEndOfWord) {
        root->isEndOfWord = false;
        return !hasChildren(root);
    }
    return false;
}

// Função para imprimir a Trie no formato de árvore
void printTrie(TrieNode* root, char* prefix, int level, bool isLast) {
    if (!root) return;

    if (level > 0) {
        printf("%*s", (level - 1) * 4, "");  // Espaçamento
        printf(isLast ? "└── " : "├── ");
        printf("%c\n", prefix[level - 1]);
    }

    int count = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            count++;

    int printed = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i]) {
            prefix[level] = i + 'a';
            printTrie(root->children[i], prefix, level + 1, printed == count - 1);
            printed++;
        }
    }
}

// Interface no console para interagir com a Trie
void menu() {
    TrieNode* root = createNode();
    int choice;
    char word[100];

    while (1) {
        printf("\n--- MENU ---\n");
        printf("1. Inserir palavra\n");
        printf("2. Buscar palavra\n");
        printf("3. Remover palavra\n");
        printf("4. Exibir Trie\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &choice);
        getchar(); // Consumir a nova linha deixada pelo scanf

        switch (choice) {
            case 1:
                printf("Digite a palavra para inserir: ");
                scanf("%s", word);
                insert(root, word);
                printf("Palavra '%s' inserida com sucesso!\n", word);
                break;
            case 2:
                printf("Digite a palavra para buscar: ");
                scanf("%s", word);
                if (search(root, word))
                    printf("Palavra '%s' encontrada na Trie!\n", word);
                else
                    printf("Palavra '%s' NÃO encontrada na Trie!\n", word);
                break;
            case 3:
                printf("Digite a palavra para remover: ");
                scanf("%s", word);
                if (search(root, word)) {
                    removeWord(root, word, 0);
                    printf("Palavra '%s' removida com sucesso!\n", word);
                } else {
                    printf("Palavra '%s' não encontrada para remoção.\n", word);
                }
                break;
            case 4:
                printf("\n--- Estrutura da Trie ---\n");
                char prefix[100];
                printTrie(root, prefix, 0, true);
                break;
            case 5:
                printf("Saindo...\n");
                return;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    }
}

// Função principal
int main() {
    menu();
    return 0;
}