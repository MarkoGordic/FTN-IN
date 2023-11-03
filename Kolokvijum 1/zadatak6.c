#include <stdio.h>
#include <stdlib.h>
#define max 50

int main(){
    int n;
    int nizA[max] = {0};

    do{
        printf("n = ");
        scanf("%d", &n);
    }while(n > 50 || n < 0);

    printf("Unesite elemente niza A: ");
    for(int i = 0; i < n; i++){
        scanf(" %d", &nizA[i]);
    }

    int indexMin = 0, indexMax = 0;
    for(int i = 1; i < n; i++){
        if(nizA[indexMax] < nizA[i])
            indexMax = i;
        else if(nizA[indexMin] > nizA[i])
            indexMin = i;
    }

    int tmp = nizA[indexMin];
    nizA[indexMin] = nizA[indexMax];
    nizA[indexMax] = tmp;

    printf("\nNiz nakon modifikacije : ");
    for (int i = 0; i < n; i++){
        printf("%d ",nizA[i]);
    }

    return 0;
}