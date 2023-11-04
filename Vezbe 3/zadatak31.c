#include <stdio.h>
#include <stdlib.h>
#define MAX 100

int main(){
    int n;

    printf("Unesite n : ");
    scanf("%d",&n);

    int nizA[MAX] = {0};
    int nizB[MAX] = {0};

    printf("Unesite niz A: ");
    for(int i = 0; i < n; i++)
        scanf("%d", &nizA[i]);

    printf("Niz B : ");
    for(int i = 0; i < n-1; i++){
        nizB[i] = nizA[i] + nizA[i+1];
        printf("%d ", nizB[i]);
    }

    return 0;
}