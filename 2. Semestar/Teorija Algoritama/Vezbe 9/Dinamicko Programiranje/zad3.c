#include <stdio.h>
#include <stdlib.h>

int min_skokova(int* niz, int n){
    int skokovi[n];

    for(int i = 0; i < n; i++){
        skokovi[i] = -1;
    }

    skokovi[0] = 0;

    for(int i = 1; i < n; i++){
        for(int j = 0; j < i; j++){
            if(j + niz[j] >= i && niz[j] != -1){
                skokovi[i] = skokovi[j] + 1;
                break;
            }
        }
    }

    return skokovi[n-1];
}

int main(){
    int niz[11] = {1, 3, 5, 8, 9, 2, 6, 7, 6, 8, 9};
    int n = 11;

    printf("Minimalan broj skokova je %d.", min_skokova(niz, n));

    return 0;
}