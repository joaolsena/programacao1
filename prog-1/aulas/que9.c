#include <stdio.h>
#include <stdlib.h>
int main(){
int vector[10], soma;
for (int i = 0; i < 10; i++)
{
   printf("%d: ", i);
   scanf("%d", &vector[i]);
}
putchar('[');
for (int i = 0; i < 10; i++)
{
    printf("%d,", vector[i]);
    soma+=vector[i];

}
putchar(']');
putchar('\n');

printf("soma= %d\n", soma);


}