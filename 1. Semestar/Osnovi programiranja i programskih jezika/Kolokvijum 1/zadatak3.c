#include <stdio.h>
#include <stdlib.h>
#define max 50

int main(){
    int n = 0;
    int nizA[max] = {0};
    
    do{
        printf("n = ");
        scanf("%d", &n);
    }while(n < 0 || n > 50);

    printf("Unesite elemente niza A: ");
    for(int i = 0; i < n; i++){
        scanf(" %d", &nizA[i]);
    }

    int min=-1;

    for(int i = 0; i < n; i++){
        if(min==-1 && nizA[i]>0)
            min=nizA[i];
        if(min!=-1 && min>nizA[i] && nizA[i]>0 )
            min=nizA[i];

    }

    if (min == -1)
        printf("banana");
    else
        printf("Najmanji pozitivan element niza je: %d", min);
    

    return 0;
}