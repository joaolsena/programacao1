#include <stdio.h>
#include <stdlib.h>
int main(){
float vector[10], soma, alunos;
for (int i = 0; i <10; i++)
{
    printf("insira a nota do aluno %d:", i+1);
    scanf("%f", &vector[i]);
    soma+=vector[i];
    alunos++;
}
putchar('\n');
printf("notas dos alunos: ");
for (int i = 0; i < 10; i++)
{
    printf("%.2f, ", vector[i]);
}
putchar('\n');
printf("media final da turma= %.2f\n", soma/alunos);

}
