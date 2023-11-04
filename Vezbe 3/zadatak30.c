#include <stdio.h>
#define MAX 100

int main(){
    int n;

    printf("Unesite n : ");
    scanf("%d", &n);

    int nizA[MAX] = {0};

    printf("Unesite niz A: ");
    for(int i = 0; i < n; i++)
        scanf("%d", &nizA[i]);

    int prviParni = -1, poslednjiNeparni = 0;
    for(int i = 0; i < n; i++){
        if(prviParni == -1 && nizA[i] % 2 == 0)
            prviParni = i;

        if(nizA[i] % 2 == 1)
            poslednjiNeparni = i;
    }

    int tmp = nizA[prviParni];
    nizA[prviParni] = nizA[poslednjiNeparni];
    nizA[poslednjiNeparni] = tmp;

    printf("Novi niz A : ");
    for(int i = 0; i < n; i++){
        printf("%d ", nizA[i]);
    }

    return 0;
}