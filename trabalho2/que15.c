#include <stdio.h>
int main(){
    int n, s=0, r=1;
    printf("insira um numero\n");
    scanf("%d", &n);
    while (r<=n/2) {
        if(n %r==0){
            s+=r;
        }
        r++;
    }
    printf("%d\n", s);
    if(s==n){
        printf("é um numero primo\n");
    } else {
        printf("nao é um numero primo\n");
    }
    return 0;
    
}