#include <stdio.h>
int main(){

int n, soma = 0, metade = 0, z = 0;

    scanf("%d", &n);
    int a[n];

for(int i = 0; i<n; i++){

    scanf("%d", &a[i]);

    soma += a[i];

}


do{

    metade += a[z];

z++;

}while(metade < soma/2);

printf("%d\n", z);




    return 0;
}