#include <stdio.h>
#include <stdlib.h>

// ---------------------------------------------------
// Variáveis globais definindo a ordem e os mínimos
// ---------------------------------------------------
int ORDER;              // Ordem da árvore (3 a 7)
int MIN_LEAF_KEYS;      // Mínimo de chaves em nós folha = floor((ORDER - 1) / 2)
int MIN_INTERNAL_KEYS;  // Mínimo de chaves em nós internos (não-raiz) = ceil(ORDER / 2) - 1

// ---------------------------------------------------
// Estrutura de nó da árvore B+
// ---------------------------------------------------
typedef struct BPlusTreeNode {
    int isLeaf;                           // 1 se nó folha, 0 se nó interno
    int num_keys;                         // número de chaves armazenadas
    int *keys;                            // array de chaves (tamanho ORDER)
    struct BPlusTreeNode **pointers;      // array de ponteiros (tamanho ORDER+1)
    struct BPlusTreeNode *parent;         // ponteiro para o nó pai
    struct BPlusTreeNode *next;           // para encadear folhas
} BPlusTreeNode;

// ---------------------------------------------------
// Cria um nó (folha ou interno) alocando arrays de tamanho ORDER+1
// ---------------------------------------------------
BPlusTreeNode* createNode(int isLeaf) {
    BPlusTreeNode *node = (BPlusTreeNode*)malloc(sizeof(BPlusTreeNode));
    node->isLeaf = isLeaf;
    node->num_keys = 0;
    node->parent = NULL;
    node->next = NULL;
    node->keys = (int*)malloc(sizeof(int) * ORDER);
    node->pointers = (BPlusTreeNode**)malloc(sizeof(BPlusTreeNode*) * (ORDER + 1));
    for (int i = 0; i < ORDER + 1; i++) {
        node->pointers[i] = NULL;
    }
    return node;
}

// ---------------------------------------------------
// Encontra a folha onde a chave deveria estar
// ---------------------------------------------------
BPlusTreeNode* findLeaf(BPlusTreeNode *root, int key) {
    if (!root) return NULL;
    BPlusTreeNode *current = root;
    while (!current->isLeaf) {
        int i = 0;
        while (i < current->num_keys && key >= current->keys[i]) {
            i++;
        }
        current = current->pointers[i];
    }
    return current;
}

// ---------------------------------------------------
// Insere uma chave em um nó folha que possua espaço
// ---------------------------------------------------
void insertIntoLeaf(BPlusTreeNode *leaf, int key) {
    int i = 0;
    while (i < leaf->num_keys && leaf->keys[i] < key) {
        i++;
    }
    for (int j = leaf->num_keys; j > i; j--) {
        leaf->keys[j] = leaf->keys[j - 1];
    }
    leaf->keys[i] = key;
    leaf->num_keys++;
}

// ---------------------------------------------------
// Declaração antecipada para inserir em nós internos
// ---------------------------------------------------
void insertIntoInternal(BPlusTreeNode **root, BPlusTreeNode *parent, int key, BPlusTreeNode *rightChild);

// ---------------------------------------------------
// Divide uma folha cheia, inserindo a nova chave
// ---------------------------------------------------
void splitLeaf(BPlusTreeNode **root, BPlusTreeNode *leaf, int key) {
    BPlusTreeNode *newLeaf = createNode(1);
    int *tempKeys = (int*)malloc(sizeof(int) * (ORDER + 1));
    int i = 0, j = 0;

    // Copia chaves existentes + nova
    while (i < leaf->num_keys && leaf->keys[i] < key) {
        tempKeys[j++] = leaf->keys[i++];
    }
    tempKeys[j++] = key;
    while (i < leaf->num_keys) {
        tempKeys[j++] = leaf->keys[i++];
    }
    int total = j;
    int split = (ORDER + 1) / 2; // ex: se ORDER=3, split=2

    leaf->num_keys = 0;
    for (i = 0; i < split; i++) {
        leaf->keys[i] = tempKeys[i];
        leaf->num_keys++;
    }
    for (; i < total; i++) {
        newLeaf->keys[newLeaf->num_keys++] = tempKeys[i];
    }
    free(tempKeys);

    // Ajusta o encadeamento de folhas
    newLeaf->next = leaf->next;
    leaf->next = newLeaf;
    newLeaf->parent = leaf->parent;

    // Promove a primeira chave da newLeaf
    int newKey = newLeaf->keys[0];

    // Se não tem pai, cria nova raiz
    if (leaf->parent == NULL) {
        BPlusTreeNode *newRoot = createNode(0);
        newRoot->keys[0] = newKey;
        newRoot->pointers[0] = leaf;
        newRoot->pointers[1] = newLeaf;
        newRoot->num_keys = 1;
        leaf->parent = newRoot;
        newLeaf->parent = newRoot;
        *root = newRoot;
    } else {
        // Insere newKey no nó interno pai
        insertIntoInternal(root, leaf->parent, newKey, newLeaf);
    }
}

// ---------------------------------------------------
// Insere chave + ponteiro (rightChild) em um nó interno
// ---------------------------------------------------
void insertIntoInternal(BPlusTreeNode **root, BPlusTreeNode *parent, int key, BPlusTreeNode *rightChild) {
    int i = 0;
    while (i < parent->num_keys && parent->keys[i] < key) {
        i++;
    }
    // Desloca chaves e ponteiros
    for (int j = parent->num_keys; j > i; j--) {
        parent->keys[j] = parent->keys[j - 1];
    }
    for (int j = parent->num_keys + 1; j > i + 1; j--) {
        parent->pointers[j] = parent->pointers[j - 1];
    }
    parent->keys[i] = key;
    parent->pointers[i + 1] = rightChild;
    parent->num_keys++;
    rightChild->parent = parent;

    // Se o nó interno encheu (num_keys == ORDER), divide
    if (parent->num_keys == ORDER) {
        int split = parent->num_keys / 2; // ex: se ORDER=4, split=2
        int promotedKey = parent->keys[split];

        BPlusTreeNode *newInternal = createNode(0);
        newInternal->num_keys = parent->num_keys - split - 1;

        // Copia as chaves + ponteiros p/ newInternal
        for (int j = 0; j < newInternal->num_keys; j++) {
            newInternal->keys[j] = parent->keys[split + 1 + j];
        }
        for (int j = 0; j < newInternal->num_keys + 1; j++) {
            newInternal->pointers[j] = parent->pointers[split + 1 + j];
            if (newInternal->pointers[j]) {
                newInternal->pointers[j]->parent = newInternal;
            }
        }
        parent->num_keys = split;

        // Se não tem pai, cria nova raiz
        if (parent->parent == NULL) {
            BPlusTreeNode *newRoot = createNode(0);
            newRoot->keys[0] = promotedKey;
            newRoot->pointers[0] = parent;
            newRoot->pointers[1] = newInternal;
            newRoot->num_keys = 1;
            parent->parent = newRoot;
            newInternal->parent = newRoot;
            *root = newRoot;
        } else {
            // Insere a chave promovida no pai
            insertIntoInternal(root, parent->parent, promotedKey, newInternal);
        }
    }
}

// ---------------------------------------------------
// Insere uma chave na árvore B+
// ---------------------------------------------------
void insert(BPlusTreeNode **root, int key) {
    if (*root == NULL) {
        // Cria primeira folha
        BPlusTreeNode *newLeaf = createNode(1);
        newLeaf->keys[0] = key;
        newLeaf->num_keys = 1;
        *root = newLeaf;
    } else {
        // Encontra folha
        BPlusTreeNode *leaf = findLeaf(*root, key);
        // Se tem espaço
        if (leaf->num_keys < ORDER - 1) {
            insertIntoLeaf(leaf, key);
        } else {
            // Divide a folha
            splitLeaf(root, leaf, key);
        }
    }
}

// ---------------------------------------------------
// Busca uma chave na B+ (retorna nó folha se encontrada)
// ---------------------------------------------------
BPlusTreeNode* search(BPlusTreeNode *root, int key) {
    if (!root) return NULL;
    BPlusTreeNode *leaf = findLeaf(root, key);
    for (int i = 0; i < leaf->num_keys; i++) {
        if (leaf->keys[i] == key) {
            return leaf;
        }
    }
    return NULL;
}

// ---------------------------------------------------
// Imprime a árvore nível a nível
// ---------------------------------------------------
void printTree(BPlusTreeNode *root) {
    if (!root) return;
    BPlusTreeNode **queue = (BPlusTreeNode**)malloc(sizeof(BPlusTreeNode*) * 1000);
    int front = 0, rear = 0;
    int level = 0;
    queue[rear++] = root;

    while (front < rear) {
        int count = rear - front;
        printf("Nível %d: ", level);
        while (count--) {
            BPlusTreeNode *node = queue[front++];
            printf("[");
            for (int i = 0; i < node->num_keys; i++) {
                printf("%d", node->keys[i]);
                if (i < node->num_keys - 1) printf(" ");
            }
            printf("] ");
            if (!node->isLeaf) {
                for (int i = 0; i <= node->num_keys; i++) {
                    if (node->pointers[i]) {
                        queue[rear++] = node->pointers[i];
                    }
                }
            }
        }
        printf("\n");
        level++;
    }
    free(queue);
}

// ---------------------------------------------------
// Ajusta nós internos após mesclagem/redistribuição
// ---------------------------------------------------
void fixInternalNode(BPlusTreeNode **root, BPlusTreeNode *node) {
    // Se o node for a raiz e estiver vazio, promove o filho
    if (node == *root) {
        if (node->num_keys == 0 && !node->isLeaf) {
            *root = node->pointers[0];
            (*root)->parent = NULL;
            free(node->keys);
            free(node->pointers);
            free(node);
        }
        return;
    }
    // Se não tem underflow, sai
    if (node->num_keys >= MIN_INTERNAL_KEYS) {
        return;
    }
    // Se há underflow, tenta redistribuir ou mesclar
    BPlusTreeNode *parent = node->parent;
    int index = -1;
    for (int i = 0; i <= parent->num_keys; i++) {
        if (parent->pointers[i] == node) {
            index = i;
            break;
        }
    }
    BPlusTreeNode *leftSibling = (index > 0) ? parent->pointers[index - 1] : NULL;
    BPlusTreeNode *rightSibling = (index < parent->num_keys) ? parent->pointers[index + 1] : NULL;

    // Tenta redistribuir do irmão esquerdo
    if (leftSibling && leftSibling->num_keys > MIN_INTERNAL_KEYS) {
        // Desloca para a direita no node
        for (int i = node->num_keys; i > 0; i--) {
            node->keys[i] = node->keys[i - 1];
            node->pointers[i + 1] = node->pointers[i];
        }
        node->pointers[1] = node->pointers[0];

        // Puxa a chave do pai
        node->keys[0] = parent->keys[index - 1];
        node->pointers[0] = leftSibling->pointers[leftSibling->num_keys];
        if (node->pointers[0]) {
            node->pointers[0]->parent = node;
        }
        node->num_keys++;
        // Atualiza o pai
        parent->keys[index - 1] = leftSibling->keys[leftSibling->num_keys - 1];
        leftSibling->num_keys--;
        return;
    }

    // Tenta redistribuir do irmão direito
    if (rightSibling && rightSibling->num_keys > MIN_INTERNAL_KEYS) {
        node->keys[node->num_keys] = parent->keys[index];
        node->pointers[node->num_keys + 1] = rightSibling->pointers[0];
        if (node->pointers[node->num_keys + 1]) {
            node->pointers[node->num_keys + 1]->parent = node;
        }
        node->num_keys++;
        parent->keys[index] = rightSibling->keys[0];
        // Desloca no rightSibling
        for (int i = 0; i < rightSibling->num_keys - 1; i++) {
            rightSibling->keys[i] = rightSibling->keys[i + 1];
            rightSibling->pointers[i] = rightSibling->pointers[i + 1];
        }
        rightSibling->pointers[rightSibling->num_keys - 1] = rightSibling->pointers[rightSibling->num_keys];
        rightSibling->num_keys--;
        return;
    }

    // Se não pode redistribuir, mescla
    if (leftSibling) {
        // Puxa a chave do pai
        leftSibling->keys[leftSibling->num_keys] = parent->keys[index - 1];
        leftSibling->num_keys++;
        // Copia as chaves do node
        for (int i = 0; i < node->num_keys; i++) {
            leftSibling->keys[leftSibling->num_keys + i] = node->keys[i];
        }
        // Copia ponteiros
        for (int i = 0; i <= node->num_keys; i++) {
            leftSibling->pointers[leftSibling->num_keys + i] = node->pointers[i];
            if (leftSibling->pointers[leftSibling->num_keys + i]) {
                leftSibling->pointers[leftSibling->num_keys + i]->parent = leftSibling;
            }
        }
        leftSibling->num_keys += node->num_keys;

        // Remove 'node' do pai
        for (int i = index - 1; i < parent->num_keys - 1; i++) {
            parent->keys[i] = parent->keys[i + 1];
        }
        for (int i = index; i < parent->num_keys; i++) {
            parent->pointers[i] = parent->pointers[i + 1];
        }
        parent->num_keys--;
        free(node->keys);
        free(node->pointers);
        free(node);

        fixInternalNode(root, parent);
    } else if (rightSibling) {
        // Mescla com o irmão direito
        node->keys[node->num_keys] = parent->keys[index];
        node->num_keys++;
        for (int i = 0; i < rightSibling->num_keys; i++) {
            node->keys[node->num_keys + i] = rightSibling->keys[i];
        }
        for (int i = 0; i <= rightSibling->num_keys; i++) {
            node->pointers[node->num_keys + i] = rightSibling->pointers[i];
            if (node->pointers[node->num_keys + i]) {
                node->pointers[node->num_keys + i]->parent = node;
            }
        }
        node->num_keys += rightSibling->num_keys;

        // Remove rightSibling do pai
        for (int i = index; i < parent->num_keys - 1; i++) {
            parent->keys[i] = parent->keys[i + 1];
        }
        for (int i = index + 1; i < parent->num_keys + 1; i++) {
            parent->pointers[i] = parent->pointers[i + 1];
        }
        parent->num_keys--;
        free(rightSibling->keys);
        free(rightSibling->pointers);
        free(rightSibling);

        fixInternalNode(root, parent);
    }
}

// ---------------------------------------------------
// Remove a chave 'key' da árvore B+
// ---------------------------------------------------
void removeKey(BPlusTreeNode **root, int key) {
    if (!*root) {
        printf("Árvore vazia.\n");
        return;
    }
    // Encontra a folha
    BPlusTreeNode *leaf = findLeaf(*root, key);
    if (!leaf) {
        printf("Chave %d não encontrada.\n", key);
        return;
    }
    // Procura índice da chave
    int index = -1;
    for (int i = 0; i < leaf->num_keys; i++) {
        if (leaf->keys[i] == key) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("Chave %d não encontrada.\n", key);
        return;
    }
    // Remove a chave (shift)
    for (int i = index; i < leaf->num_keys - 1; i++) {
        leaf->keys[i] = leaf->keys[i + 1];
    }
    leaf->num_keys--;

    // Se a folha era a raiz
    if (leaf == *root) {
        // Se ficou vazia, libera
        if (leaf->num_keys == 0) {
            free(leaf->keys);
            free(leaf->pointers);
            free(leaf);
            *root = NULL;
        }
        return;
    }

    // Se não houve underflow, apenas atualiza o pai (se não for o filho da esquerda)
    if (leaf->num_keys >= MIN_LEAF_KEYS) {
        BPlusTreeNode *parent = leaf->parent;
        int leafIndex;
        for (int i = 0; i <= parent->num_keys; i++) {
            if (parent->pointers[i] == leaf) {
                leafIndex = i;
                break;
            }
        }
        // Atualiza a chave do pai, se não for o filho mais à esquerda
        if (leafIndex > 0) {
            parent->keys[leafIndex - 1] = leaf->keys[0];
        }
        return;
    }

    // Underflow: tenta redistribuir ou mesclar
    BPlusTreeNode *parent = leaf->parent;
    int leafIndex;
    for (int i = 0; i <= parent->num_keys; i++) {
        if (parent->pointers[i] == leaf) {
            leafIndex = i;
            break;
        }
    }
    BPlusTreeNode *leftSibling = (leafIndex > 0) ? parent->pointers[leafIndex - 1] : NULL;
    BPlusTreeNode *rightSibling = (leafIndex < parent->num_keys) ? parent->pointers[leafIndex + 1] : NULL;

    // Tenta redistribuir do irmão esquerdo
    if (leftSibling && leftSibling->num_keys > MIN_LEAF_KEYS) {
        // Desloca as chaves em 'leaf' para a direita
        for (int i = leaf->num_keys; i > 0; i--) {
            leaf->keys[i] = leaf->keys[i - 1];
        }
        // Pega a última chave do irmão esquerdo
        leaf->keys[0] = leftSibling->keys[leftSibling->num_keys - 1];
        leftSibling->num_keys--;
        leaf->num_keys++;
        // Atualiza o pai
        parent->keys[leafIndex - 1] = leaf->keys[0];
        return;
    }
    // Tenta redistribuir do irmão direito
    if (rightSibling && rightSibling->num_keys > MIN_LEAF_KEYS) {
        leaf->keys[leaf->num_keys] = rightSibling->keys[0];
        leaf->num_keys++;
        // Shift no irmão direito
        for (int i = 0; i < rightSibling->num_keys - 1; i++) {
            rightSibling->keys[i] = rightSibling->keys[i + 1];
        }
        rightSibling->num_keys--;
        // Atualiza o pai
        parent->keys[leafIndex] = rightSibling->keys[0];
        return;
    }
    // Mescla com o irmão
    if (leftSibling) {
        // Copia as chaves de 'leaf' para o leftSibling
        for (int i = 0; i < leaf->num_keys; i++) {
            leftSibling->keys[leftSibling->num_keys + i] = leaf->keys[i];
        }
        leftSibling->num_keys += leaf->num_keys;
        leftSibling->next = leaf->next;
        // Remove 'leaf'
        free(leaf->keys);
        free(leaf->pointers);
        free(leaf);
        // Ajusta o pai
        for (int i = leafIndex - 1; i < parent->num_keys - 1; i++) {
            parent->keys[i] = parent->keys[i + 1];
        }
        for (int i = leafIndex; i < parent->num_keys; i++) {
            parent->pointers[i] = parent->pointers[i + 1];
        }
        parent->num_keys--;
        // Ajusta nó interno se precisar
        fixInternalNode(root, parent);
    } else if (rightSibling) {
        // Mescla 'leaf' com o irmão direito
        for (int i = 0; i < rightSibling->num_keys; i++) {
            leaf->keys[leaf->num_keys + i] = rightSibling->keys[i];
        }
        leaf->num_keys += rightSibling->num_keys;
        leaf->next = rightSibling->next;
        free(rightSibling->keys);
        free(rightSibling->pointers);
        free(rightSibling);
        // Ajusta o pai
        for (int i = leafIndex; i < parent->num_keys - 1; i++) {
            parent->keys[i] = parent->keys[i + 1];
        }
        for (int i = leafIndex + 1; i < parent->num_keys + 1; i++) {
            parent->pointers[i] = parent->pointers[i + 1];
        }
        parent->num_keys--;
        fixInternalNode(root, parent);
    }
}

// ---------------------------------------------------
// Menu principal
// ---------------------------------------------------
int main() {
    BPlusTreeNode *root = NULL;
    int choice, key, orderInput;

    // Pede a ordem
    do {
        printf("Digite a ordem da árvore B+ (3, 4, 5, 6 ou 7): ");
        scanf("%d", &orderInput);
        if (orderInput < 3 || orderInput > 7) {
            printf("Ordem inválida!\n");
        }
    } while (orderInput < 3 || orderInput > 7);

    ORDER = orderInput;
    MIN_LEAF_KEYS = (ORDER - 1) / 2;
    MIN_INTERNAL_KEYS = ((ORDER + 1) / 2) - 1;

    do {
        printf("\nMenu:\n");
        printf("1. Inserir chave\n");
        printf("2. Buscar chave\n");
        printf("3. Remover chave\n");
        printf("4. Imprimir árvore B+\n");
        printf("5. Sair\n");
        printf("Digite sua opção: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Digite a chave para inserir: ");
                scanf("%d", &key);
                insert(&root, key);
                printf("Chave %d inserida!\n", key);
                break;
            case 2: {
                printf("Digite a chave para buscar: ");
                scanf("%d", &key);
                BPlusTreeNode *res = search(root, key);
                if (res) {
                    printf("Chave %d encontrada na folha: ", key);
                    for (int i = 0; i < res->num_keys; i++) {
                        printf("%d ", res->keys[i]);
                    }
                    printf("\n");
                } else {
                    printf("Chave %d não encontrada.\n", key);
                }
                break;
            }
            case 3:
                printf("Digite a chave para remover: ");
                scanf("%d", &key);
                removeKey(&root, key);
                break;
            case 4:
                printf("Árvore B+:\n");
                printTree(root);
                break;
            case 5:
                printf("Encerrando...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (choice != 5);

    return 0;
}
