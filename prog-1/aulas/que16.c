#include <stdio.h>
#define max_numeros 3
void nota(int n[max_numeros], int p[max_numeros]){
    float f=0;
     int pe=0;
    for (int i = 0; i < max_numeros; i++)
    {
        f += n[i]*p[i];
        pe+=p[i];
    }

    f=f/pe;

    printf("%.2f\n", f);
}
int main(){
    int n[max_numeros];
    int p[max_numeros];
    for (int i = 0; i <max_numeros; i++)
    {
        printf("mumero peso ");
        scanf("%d %d",&n[i], &p[i]);
    }
    nota(n,p);

}