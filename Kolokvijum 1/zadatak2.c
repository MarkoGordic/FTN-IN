#include <stdio.h>
#include <stdlib.h>
#define max 25
int main(){
    int n;
    do {
        printf("Ispisati duzinu niza ");
        scanf("%d", &n);
    }while(n<0 || n>25);

    int nizA[max]={0};
    int nizB[max]={0};

    printf("Uneti elemente niza A ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d",&nizA[i]);
    }

    for (int i = 0; i < n; i++){
        if(nizA[i]%2==0)
            nizB[i]=nizA[i]+1;
        else
            nizB[i]=nizA[i]*2;
    }

    int proizvod=nizB[0];

    for (int i = 1; i < n; i++){
        
        proizvod=nizB[i]*proizvod;
    }

    printf("Elementi niza B: ");
    for (int i = 0; i < n; i++){

        printf("%d ",nizB[i]);
        
        
    }

    printf("\nProizvod elemenata niza B je %d",proizvod);





    
    




    return 0;
}