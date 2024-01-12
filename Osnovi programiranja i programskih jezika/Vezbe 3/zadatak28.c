#include <stdio.h>

int main(){
    int n;

    printf("Unesite n : ");
    scanf("%d", &n);

    int last = n % 10;

    while(n / 10 > 0)
        n = n / 10;

    int first = n;

    printf("Suma prve i poslednje cifre je %d.\n", first + last);

    return 0;
}