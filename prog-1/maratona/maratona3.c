#include <stdio.h>

int main() {
    int P;
    scanf("%d", &P);

    int n = P / 2;
    int pos = 1;  
    int shuffles = 0;

    do {
        if (pos < n) {
            pos = 2 * pos + 1;  
        } else {
            pos = 2 * (pos - n);
        }
        shuffles++;
    } while (pos != 1);

    printf("%d\n", shuffles);

    return 0;
}