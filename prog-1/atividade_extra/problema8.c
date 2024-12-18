#include <stdio.h>
#include <stdlib.h>
int main(){
    int s, t, f, chegada;
   scanf("%d %d %d", &s, &t, &f);
   if (s==0)
   {
    s+=24;
   }
   
   chegada= s+t+f;
   if(chegada>=24)
   chegada-=24;
   printf("%d\n", chegada);

    
}