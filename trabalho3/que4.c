#include <stdio.h>
#include <stdlib.h>

int main(){
    int h=1, p;
    do
    {
        if (h<0)
        {
            printf("numero invalido.\n");
        } else if(h>30)
        { 
            printf("numero muito grande.\n");}
            else if(p!=1 && p!=2){
                printf("pode somente 1 e 2.\n");
            }

        printf("insira o lado do quadrado entre 1 e 30: ");
        scanf("%d", &h);

        printf("insira o numero da opcao que deseja:\n1) preenchido.\n2) vazado.\n");
        scanf("%d", &p);
        
    } while (h<0|| h>30 || p!=1 && p!=2);

    switch (p)
    {
    case 1:
        for (int i = 0; i < h; i++)
        {
            for(int k= 3; k>=0; k--) printf("  ");
            for (int j = 0; j < h; j++)
            {
                putchar('*');
            }
            putchar('\n');
        }
        
        break;
        case 2:

        for (int i = 0; i < h; i++)
        {
            for(int k= 3; k>=0; k--) printf("  ");
            for (int j = 0; j < h; j++)
            {
                if(j==0 || i==0 ||i== h-1 || j == h-1 ){
                putchar('*');}
                else putchar(' ');
            }
            putchar('\n');
        }


        break;
    
    default:
        break;
    }
    
}