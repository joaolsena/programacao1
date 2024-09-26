#include <stdio.h>
int main(){
    int i, p;
    for ( p = 1; p < 10; p++)
    {
     printf ("\ninsira a idade do aluno %d\n", p);
    scanf("%d", &i);
    if (i<=0){
        printf("ta no saco do pai ainda\n");
    } else{
    printf ("---------------------------------------");
    printf ("\na idade do aluno %d é %d\n",p, i);
    }
    }
    return 0;
}