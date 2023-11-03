#include <stdio.h>
#include <stdlib.h>
#define max 100

int main(){
    int n;
    int nizA[max] = {0};
    float prosek = 0;
    int brojac = 0;

    do{
        printf("n = ");
        scanf("%d", &n);
    }while(n > 100 || n < 0);

    printf("Unesite elemente niza A: ");
    for(int i = 0; i < n; i++){
        scanf(" %d", &nizA[i]);
    }

    printf("Trazeni brojevi su : ");
    for(int i = 0; i < n; i++){
        if(nizA[i] % 10 == 7){
            printf("%d ", nizA[i]);
            prosek = prosek + (float)nizA[i];
            brojac++;
        }
    }

    prosek = prosek / (float)brojac;

    if(brojac == 0)
        printf("Nema takvih elemenata.");
    else
        printf("\nProsek je %.3f", prosek);

    return 0;
}