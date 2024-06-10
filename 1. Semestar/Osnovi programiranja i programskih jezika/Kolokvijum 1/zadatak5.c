#include <stdio.h>
#include <stdlib.h>
#define max 50

int main(){
    int n;
    int nizA[max] = {0};
    //int indexi[max] = {0};
    int brojac = 0;

    do{
        printf("n = ");
        scanf("%d", &n);
    }while(n > 50 || n < 0);

    printf("Unesite elemente niza A: ");
    for(int i = 0; i < n; i++){
        scanf(" %d", &nizA[i]);
    }

    printf("Trazeni elementi su : ");
    for(int i = 0; i < n; i++){
        if(i % 2 != 0 && nizA[i] % 2 == 0){
            printf("%d ", nizA[i]);
            //indexi[brojac] = i;
            brojac++;
        }
    }

    printf("\nIma ih %d", brojac);

    /*
    printf("\nIndexi : ");
    for (int i = 0; i < brojac; i++){
        printf("%d ",indexi[i]);
    }
    */

    return 0;
}