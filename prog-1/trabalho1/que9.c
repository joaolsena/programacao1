#include <stdio.h>
int main(){
    float f,c;
    printf("insira a temperatura em graus Fahrenheit:\n");
    scanf("%f", &f);
    c=(f-32)*5/9;
    printf("a temperatura em celsius é:%.2f\n",c);
    return 0;
}