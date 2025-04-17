#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TAMANHO_ALFABETO 26

// Estrutura do nó da Trie
typedef struct NoTrie {
    struct NoTrie* filhos[TAMANHO_ALFABETO];
    bool fimDePalavra;
} NoTrie;

// Cria um novo nó da Trie
NoTrie* criarNo() {
    NoTrie* novoNo = (NoTrie*)malloc(sizeof(NoTrie));
    if (novoNo) {
        novoNo->fimDePalavra = false;
        for (int i = 0; i < TAMANHO_ALFABETO; i++)
            novoNo->filhos[i] = NULL;
    }
    return novoNo;
}

// Insere uma palavra na Trie
void inserir(NoTrie* raiz, const char* palavra) {
    NoTrie* no = raiz;
    while (*palavra) {
        int indice = *palavra - 'a';
        if (!no->filhos[indice])
            no->filhos[indice] = criarNo();
        no = no->filhos[indice];
        palavra++;
    }
    no->fimDePalavra = true;
}

// Busca uma palavra na Trie
bool buscar(NoTrie* raiz, const char* palavra) {
    NoTrie* no = raiz;
    while (*palavra) {
        int indice = *palavra - 'a';
        if (!no->filhos[indice])
            return false;
        no = no->filhos[indice];
        palavra++;
    }
    return no->fimDePalavra;
}

// Verifica se um nó possui filhos
bool temFilhos(NoTrie* no) {
    for (int i = 0; i < TAMANHO_ALFABETO; i++)
        if (no->filhos[i])
            return true;
    return false;
}

// Remove uma palavra da Trie
bool removerPalavra(NoTrie* raiz, const char* palavra, int profundidade) {
    if (!raiz)
        return false;

    if (*palavra) {
        int indice = *palavra - 'a';
        if (raiz->filhos[indice] &&
            removerPalavra(raiz->filhos[indice], palavra + 1, profundidade + 1) &&
            !raiz->fimDePalavra) {
            if (!temFilhos(raiz->filhos[indice])) {
                free(raiz->filhos[indice]);
                raiz->filhos[indice] = NULL;
                return !temFilhos(raiz);
            }
        }
    } else if (raiz->fimDePalavra) {
        raiz->fimDePalavra = false;
        return !temFilhos(raiz);
    }
    return false;
}

// Imprime a Trie no formato de árvore
void imprimirTrie(NoTrie* raiz, char* prefixo, int nivel, bool ehUltimo) {
    if (!raiz) return;

    if (nivel > 0) {
        printf("%*s", (nivel - 1) * 4, "");  // Espaçamento
        printf(ehUltimo ? "└── " : "├── ");
        printf("%c\n", prefixo[nivel - 1]);
    }

    int totalFilhos = 0;
    for (int i = 0; i < TAMANHO_ALFABETO; i++)
        if (raiz->filhos[i])
            totalFilhos++;

    int impressos = 0;
    for (int i = 0; i < TAMANHO_ALFABETO; i++) {
        if (raiz->filhos[i]) {
            prefixo[nivel] = i + 'a';
            imprimirTrie(raiz->filhos[i], prefixo, nivel + 1, impressos == totalFilhos - 1);
            impressos++;
        }
    }
}

// Interface do menu no console
void menu() {
    NoTrie* raiz = criarNo();
    int opcao;
    char palavra[100];

    while (1) {
        printf("\n--- MENU ---\n");
        printf("1. Inserir palavra\n");
        printf("2. Buscar palavra\n");
        printf("3. Remover palavra\n");
        printf("4. Exibir Trie\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Consumir a nova linha deixada pelo scanf

        switch (opcao) {
            case 1:
                printf("Digite a palavra para inserir: ");
                scanf("%s", palavra);
                inserir(raiz, palavra);
                printf("Palavra '%s' inserida com sucesso!\n", palavra);
                break;
            case 2:
                printf("Digite a palavra para buscar: ");
                scanf("%s", palavra);
                if (buscar(raiz, palavra))
                    printf("Palavra '%s' encontrada na Trie!\n", palavra);
                else
                    printf("Palavra '%s' NÃO encontrada na Trie!\n", palavra);
                break;
            case 3:
                printf("Digite a palavra para remover: ");
                scanf("%s", palavra);
                if (buscar(raiz, palavra)) {
                    removerPalavra(raiz, palavra, 0);
                    printf("Palavra '%s' removida com sucesso!\n", palavra);
                } else {
                    printf("Palavra '%s' não encontrada para remoção.\n", palavra);
                }
                break;
            case 4:
                printf("\n--- Estrutura da Trie ---\n");
                char prefixo[100];
                imprimirTrie(raiz, prefixo, 0, true);
                break;
            case 5:
                printf("Encerrando o programa...\n");
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
