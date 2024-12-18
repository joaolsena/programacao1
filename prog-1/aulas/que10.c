#include <stdio.h>
#include <stdlib.h>
int main(){
int vector1[5] ={2,5,7,1,9};
int vector2[5] = {3,4,6,1,9}; 
int vector3[5];
int soma=0;
for (int i = 0; i < 5; i++)
{
    vector3[i]= vector1[i] + vector2[i];
}
for (int i = 0; i <5; i++)
{
    printf("%d, ", vector1[i]);
}
putchar('\n');
for (int i = 0; i < 5; i++)
{
    printf("%d, ", vector2[i]);
}
putchar('\n');
printf("========== a soma dos vetores ===========\n");
for (int i = 0; i < 5; i++)
{
    printf("%d, ", vector3[i]);
}
putchar('\n');



}