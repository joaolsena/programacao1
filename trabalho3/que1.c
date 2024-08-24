#include <stdio.h>
int main(){
    int n,v=1;
    printf ("insira a altura do triangulo de pascal\n");
    scanf("%d", &n);
    for (int i =0 ; i<n; i++)
    {
      v=1;
       for (int j = 0; j<=i; j++)
       {
      printf("%d ", v);
      v=(v*(i-j)/(j+1));
       }       
       printf("\n");
    }
    return 0;
}
