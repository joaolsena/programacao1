#include <stdio.h>
#include <stdlib.h>
int main(){
    unsigned long long  n, i=0, u=0;
scanf("%llu", &n);
u=n % 10;
while (n>0)
{
    i= i*10 +(n % 10);
    n/=10;

}
if (u==0)
{
    printf("0%llu\n", i);
}else
printf("%llu\n", i);

    
    
}