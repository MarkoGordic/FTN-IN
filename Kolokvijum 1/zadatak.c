#include <stdio.h>
#include <stdlib.h>
#define max 30

int main () {
    int n;
    do{
        printf("Uneti duzinu nizova: ");
        scanf("%d", &n);
    }while(n<0 || n>30);


    int nizA[max]={0};
    int nizB[max]={0};
    int nizC[max]={0};
    int suma=0;

    printf("Uneti elemente niza A: ");
    for(int i=0;i<n;i++ ){
        scanf(" %d",&nizA[i]);
    }

    printf("Uneti elemente niza B: ");
    for(int i=0;i<n;i++ ){
        scanf(" %d",&nizB[i]);
    }

    for(int i=0;i<n;i++ ){
        nizC[i]=abs(nizA[i]-nizB[i]);

    }
    printf("Elementi niza C: ");
    for(int i=0;i<n;i++ ){
        printf("%d ",nizC[i]);

        suma=nizC[i]+suma;

    }

    printf("\nSuma elemenata niza C je %d ",suma);











   



    



    
    return 0;
}   