// LER 4 NOTAS E MOSTRAR A MEDIA SIMPLES
// LEIA AS 4 NOTAS USANDO UM LAÇO FOR

#include <stdio.h>

int main()
{
    int altura;

    printf("Digite a altura do quadrado: ");
    scanf("%d", &altura);

    for (int i = 0; i < altura; i++)
    {
        for (int j = 0; j < altura; j++)
        {
            if (i == 0 || j==0 || i==4 || j==4 || i==1 && j!=2 || i==2 && j!=1 && j!=3 || i==3 && j!=2)
            {
                printf(" * ");
            }
            else
            {
                printf("   ");
            }
        }
        printf("\n");
    }

    return 0;
}