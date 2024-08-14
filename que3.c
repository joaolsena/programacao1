#include <stdio.h>
int main(){
float c;
printf("insira a temperatura em celsius\n");
scanf("%f", &c);
if (c>=30){
    printf("esta quente\n");
} else{
    printf("esta frio\n");
}
return 0;
}