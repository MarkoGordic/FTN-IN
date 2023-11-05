#include <stdio.h>
#define MAX 100

int main(){
    int n;

    printf("Unesite n : ");
    scanf("%d", &n);

    int nizA[MAX] = {0};

    printf("Unesite niz A: ");
    for(int i = 0; i < n; i++)
        scanf(" %d", &nizA[i]);

    int maxLen = 1, tmp = nizA[0], res = 1; 
    for(int i = 1; i < n; i++){
        if(nizA[i] >= tmp)
            maxLen++;
        else{
            if(maxLen > res)
                res = maxLen;
            maxLen = 1;
        }

        tmp = nizA[i];
    }

    printf("Maksimalna duzina neopadajuceg niza je %d.", res);

    return 0;
}