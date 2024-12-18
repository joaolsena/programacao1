#include <stdio.h>
#define max_p 2

    typedef struct 
    {
        char n[50];
        int idade;
    }pessoa;
    int main(){
        pessoa p[max_p];
        for (int i = 0; i < max_p; i++)
        {
            printf("informe o nome %d: ", i+1);
            fgets(p[i].n,50,stdin);
            printf("idade %d: ",i+1);
            scanf("%d", &p[i].idade);
            getchar();
            printf("\n");


        }
        printf("\n pessoas ai\n");
        for (int i = 0; i <max_p; i++)
        {
            printf("%s %d", p[i].n, p[i].idade);
        }
        printf("\n");
        
}