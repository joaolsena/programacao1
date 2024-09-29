#include <stdio.h>

#define MAX_PLANETAS 10000
#define MAX_PLANOS 500
int main(){
    int m,n;
    scanf("%d %d", &m, &n);
    int a[m], b[m], c[m],d[m],ae, de,be,ce;
    int x[n], y[n],z[n], xe,ye, ze;
    int calculo=0;
    for (int i = 0; i <m; i++)
    {
        scanf("%d %d %d %d", &a[i], &b[i], &c[i], &d[i]);
        de+=d[i];
        ae+=a[i];
        be+=b[i];
        ce+=c[i];
  
    }
    for (int i = 0; i <n; i++)
    {
        scanf("%d %d %d", &x[i], &y[i], &z[i]);
        xe+=x[i];
        ye+=y[i];
        ze+=z[i];

    }
    for (int i = 0; i < n; i++)
    {
        int as=0;
      for (int j = 0; j < m; j++)
      {
        calculo= (a[j]*xe+b[j]*ye+c[j]*ze);
        calculo-=((ae-a[j])*xe+(be-b[j])*ye+(ce-c[j])*ze);
        calculo-=de;
        
        
      }
      
    }
    printf("%d\n", calculo);

    
    

}

