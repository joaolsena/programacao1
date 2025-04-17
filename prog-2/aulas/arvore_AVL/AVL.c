#include <stdio.h>
#include <stdlib.h>

//criando o nó para compor a arvore
typedef struct no{
    int valor;
    struct no *esquerda;//ponteiro para a sub-arvore a esquerda
    struct no *direita;//ponteiro para a sub-arvore a direita
    int altura;//registrar altura do nó
}No;

//Função para inserir um elemento na arvore (Criar novo nó)

No *novoNo(int valor){
    No *no_novo = malloc(sizeof(No));

    if(no_novo){ //o novo nó sempre será uma folha
        no_novo->valor = valor;
        no_novo->esquerda = NULL;
        no_novo->direita = NULL;
        no_novo->altura = 0;
    }
    else{
        printf("Erro de alocação de memória\n");
    }
    return no_novo;
}

//Função para verificar e retornar o lado maior da arvore

int maior(int a, int b){
    return (a > b) ? a : b;   //retorna o maior, vai ser usado para verificar o lado maior das subarvores
}

//Função para retornar a altura da arvore

int alturaDoNo(No *no){
    if(no == NULL){
        return -1;
    }
    else{
        return no->altura;
    }
}

//Função para calcular e retornar o fator de balanceamento da arvore

int fatorDeBalanceamento(No *no){
    if(no){
        return (alturaDoNo(no->esquerda) - alturaDoNo(no->direita)); //retorna a altura do filho esquerdo - altura do filho direito
    }
    else{
        return 0;//se o no for NULL, o fator de balanceamento é 0
    }
}


No *rotacaoEsquerda(No *no){
    No *temp_x, *temp_y;//criar dois ponteiros temporarios

    //x recebe o valor do filho direito do nó, e y recebe o valor do filho esquerdo de x
    temp_x = no->direita;
    temp_y = temp_x->esquerda;

    //o nó é transferido para a esquerda de x, e y é transferido para a direita do nó
    temp_x->esquerda = no;
    no->direita = temp_y;

    //a altura do nó e de x é atualizada
    no->altura = maior(alturaDoNo(no->esquerda), alturaDoNo(no->direita)) + 1;
    temp_x->altura = maior(alturaDoNo(temp_x->esquerda), alturaDoNo(temp_x->direita)) + 1;
    
    return temp_x;
}


No *rotacaoDireita(No *no){
    No *temp_x, *temp_y;//criar dois ponteiros temporarios

    //x vira o filho esquerdo do nó, e y vira o filho direito de x
    temp_x = no->esquerda;
    temp_y = temp_x->direita;

    //o nó é transferido para a direita de x, e y é transferido para a esquerda do nó
    temp_x->direita = no;
    no->esquerda = temp_y;

    //atualizando a altura do nó e de x
    no->altura = maior(alturaDoNo(no->esquerda), alturaDoNo(no->direita)) + 1;
    temp_x->altura = maior(alturaDoNo(temp_x->esquerda), alturaDoNo(temp_x->direita)) + 1;

    return temp_x;
}


No *rotacaoDireitaEsquerda(No *no){
    no->direita = rotacaoDireita(no->direita);//rotaciona o filho direito do nó para a direita
    return rotacaoEsquerda(no);//rotaciona a subarvore do nó para a esquerda
}


No *rotacaoEsquerdaDireita(No *no){
    no->esquerda = rotacaoEsquerda(no->esquerda);//rotaciona o filho esquerdo do nó para a esquerda
    return rotacaoDireita(no);//rotaciona a subarvore do nó para a direita
}


//Função para balancear a arvore
No *balancear(No *no){
    int fB = fatorDeBalanceamento(no); //calcula o balanceamento do nó

    //rotação a esquerda
    if(fB < -1 && fatorDeBalanceamento(no->direita) <= 0){
        return rotacaoEsquerda(no);
    }

    //rotação a direita
    else if(fB > 1 && fatorDeBalanceamento(no->esquerda) >= 0){
        return rotacaoDireita(no);
    }

    //rotação a direita e depois a esquerda
    else if(fB > 1 && fatorDeBalanceamento(no->esquerda) < 0){
        no->esquerda = rotacaoEsquerda(no->esquerda);   //rotaciona o filho esquerdo para a esquerda
        return rotacaoEsquerdaDireita(no);              //rotaciona o nó a esquerda e direita
    }

    //rotação a esquerda e depois a direita
    else if(fB < -1 && fatorDeBalanceamento(no->direita) > 0){
        no->direita = rotacaoDireita(no->direita);      //rotaciona o filho direito para a direita
        return rotacaoDireitaEsquerda(no);              //rotaciona o nó a direita e esquerda
    }
    return no;
}

//função para inserir um nó na árvore
No *inserir(No *no, int x){
    if(no == NULL){//se o nó for NULL, cria um novo nó, pois a arvore está vazia naquele ponto
        return novoNo(x);
    }
         //começando pela raiz, vai verificar se x é maior ou menor que o nó atual,
         // descer um nível para esquerda ou direita, e repetir o processo até encontrar o seu lugar
    else{  
        if(x < no->valor){
            no->esquerda = inserir(no->esquerda, x);
        }
        else if(x > no->valor){
            no->direita = inserir(no->direita, x);
        }
        else{
            printf("O valor %d já existe na arvore\n", x);
        }
        //definir a altura do nó inserido
        no->altura = maior(alturaDoNo(no->esquerda), alturaDoNo(no->direita)) + 1;

        //verificar se a arvore está desbalanceada
        no = balancear(no);       

        return no;      
    }
}

//Função para remover um elemento da arvore

No *remover(No *no, int x){
    if(no == NULL){
        printf("O valor %d não existe na arvore\n", x);
        return NULL;
    }
    else{//verifica se o atual nó tem o valor de x e se tem filhos
        if(no->valor == x){
            //remover os nós folhas
            if(no->esquerda == NULL && no->direita == NULL){
                free(no);
                printf("O valor %d foi removido da arvore\n", x);
                return NULL;
            }
            
            else{
                //remover nós que possuem 2 filhos
                if(no->esquerda != NULL && no->direita != NULL){
                    No *aux = no->esquerda;
                    while(aux->direita != NULL){ //cria um ponteiro temporário q assume o valor do nó mais a direita do filho esquerdo do nó original
                        aux = aux->direita;
                    }
                    no->valor = aux->valor;//substitui a posição do nó, pelo nó copiado pelo ponteiro temporário
                    aux->valor = x;//o valor do auxiliar é o valor a ser removido, removendo o nó copiado lá de baixo
                    printf("O valor %d foi removido da arvore\n", x); 
                    no->esquerda = remover(no->esquerda, x);
                    return no;
                }
                else{
                    //remover no com 1 filho
                    No *aux;
                    if(no->esquerda != NULL){
                        aux = no->esquerda;
                    }
                    else{
                        aux = no->direita;
                    }
                    free(no);
                    printf("O valor %d foi removido da arvore\n", x);
                    return aux;
                }
            }
        }
        else{   //se o nó não tiver sido encontrado, vai verificar se o atual nó é menor ou maior do que x, e deslocar a busca para o filho da esquerda ou direita
            if(x < no->valor){
                no->esquerda = remover(no->esquerda, x);
            }
            else{
                no->direita = remover(no->direita, x);
            }


            //recalcular a altura do nó
            no->altura = maior(alturaDoNo(no->esquerda), alturaDoNo(no->direita)) + 1;

            //verificar se a arvore está desbalanceada
            no = balancear(no);

            return no;
        }
    }
}


//Função para imprimir uma visualização da árvore inteira
void printTree(No* raiz, int space) {
    if (raiz == NULL) {
        return;
    }

    // Aumenta a distância entre os níveis
    space += 10;

    // Processa o filho direito primeiro
    printTree(raiz->direita, space);

    // Imprime o nó atual após o espaço
    printf("\n");
    for (int i = 10; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", raiz->valor);

    // Processa o filho esquerdo
    printTree(raiz->esquerda, space);
}
//trabalhando no main

int main(){

    int opcao, valor;
    No *raiz = NULL;//criar a raiz da arvore


    do{
        printf("\n\n1 - Inserir\n2 - Remover\n3 - Imprimir\n4 - Sair\n\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &valor);
                raiz = inserir(raiz, valor);
                break;
            case 2:
                printf("Digite o valor a ser removido: ");
                scanf("%d", &valor);
                raiz = remover(raiz, valor);
                break;
            case 3:
                printTree(raiz, 0);
                break;
            case 4:
                printf("Saindo do programa\n");
                break;  
            default:
                printf("Opcao invalida\n");
                break;
        }
    }while(opcao != 4);
    return 0;
}
