#include <stdio.h>
#include <stdlib.h>
int main(){
    float n=0, m=0;
    int a= 0;
    
    
   
         while (n>=0)
    {
         
        printf("insira a nota do aluno %d: ", a);
        scanf("%f", &n);
        if(n>0){
        m= m+n;
         a++;}


    }
    printf("media final %.2f\n", m=m/a);
    return 0;

}
