#include <stdio.h>
#include <stdlib.h>

int main()
{
    int matriz[4][4], dp=0, ts=0, ti=0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            matriz[i][j] = rand () %10;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%2d", matriz[i][j]);
            if(i==j){
                dp += matriz[i][j];
            }
            if(i<j){
                ts+= matriz[i][j];
            }
            if(i>j){
                ti+=matriz[i][j];
            }
        }
        putchar('\n');
    }
    printf("diagonal principal= %d\n", dp);
    printf("triangulo superior= %d\n", ts);
    printf("triangular inferior= %d\n", ti);

}