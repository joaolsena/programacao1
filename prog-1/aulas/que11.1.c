#include <stdio.h>
#include <stdlib.h>
int main(){
float vector[20], soma, alunos;
for (int i = 0; i <20; i++)
{
    // da numeros aleatorios
    vector[i]= rand() %10;
    soma+=vector[i];
    alunos++;
}
putchar('\n');
printf("notas dos alunos: ");
for (int i = 0; i < 20; i++)
{
    printf("%.2f, ", vector[i]);
}
putchar('\n');
printf("media final da turma= %.2f\n", soma/alunos);

}
