#include <stdio.h>
int main(){

int ta, tb, dif, loop = 0, maior;

scanf("%d %d", &ta, &tb);

if (ta > tb){
    maior = ta;
    ta = tb;
    tb = maior;
}

do{
    dif += ta - tb;

    loop++;

}while(dif > ta || dif > tb || dif > -ta || dif > -tb );

    printf("%d\n", loop);


    return 0;
}