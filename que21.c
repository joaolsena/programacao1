#include <stdio.h>

int main() {
    int tipoProduto, quantidade;
    float preco, precoFinal, desconto;
    printf("Digite o tipo de produto (1-3): ");
    scanf("%d", &tipoProduto);

    
    printf("Digite a quantidade adquirida: ");
    scanf("%d", &quantidade);

    
    switch(tipoProduto) {
        case 1:
            preco = 10.0; 
            break;
        case 2:
            preco = 20.0; 
            break;
        case 3:
            preco = 30.0; 
            break;
        default:
            printf("Tipo de produto inválido.\n");
            

   
    precoFinal = preco * quantidade;

    if (quantidade >= 10) {
        desconto = 0.10; 
    } else if (quantidade >= 5) {
        desconto = 0.05; 
    } else {
        desconto = 0.0; 
    }

    
    precoFinal = precoFinal - (precoFinal * desconto);

    
    printf("O preço final após o desconto é: R$ %.2f\n", precoFinal);

    return 0;
}
}
