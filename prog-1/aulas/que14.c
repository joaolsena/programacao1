//leia 10 alonos e no final informe se esta aprovado opu reprvado menor que 5 reprova e ter mais de 15 faltas
#include <stdio.h>
#include <stdlib.h>
#define max_alunos 2
typedef struct 
{
    char n[50];
    float n1, n2,m;
    int f;

    
} alunos;
int main(){
alunos p[max_alunos];

for (int i = 0; i < max_alunos; i++)
{
    printf("insira o nome do alunos %d: ", i+1);
     fgets(p[i].n,50,stdin);
     printf("insira a nota 1 e nota 2 do aluno %d: ", i+1);
     scanf("%f %f", &p[i].n1, &p[i].n2);
     printf("insira as faltas do aluno %d: ", i+1);
     scanf("%d",&p[i].f);
     getchar();
}
for (int i = 0; i < max_alunos; i++)
{
    p[i].m=(p[i].n1 +p[i].n2)/2;
}
printf("\nresultado =================================\n");
for (int i = 0; i < max_alunos; i++)
{
    if (p[i].m>5 && p[i].f<15)
    {
        printf("o aluno %s está aprovado\n", p[i].n);
    } else
    printf("o aluno %s está reprovado\n", p[i].n);
    
}



}

