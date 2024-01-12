#include <stdio.h>
#define MAX 30

int main(){
    int n;
    do{
        printf("Uneti duzinu niza: ");
        scanf("%d", &n);
    }while(n<0 || n>30);

    int nizA[MAX]={0};

    printf("Uneti elemente niza A: ");
    for(int i=0;i<n;i++ ){
        scanf(" %d",&nizA[i]);
    }

    // Preko dva pokazivaca
    /*
        int* p = nizA + n - 1;
        int tmp = 0;
        for(int i = 0; i < n/2; i++){
            tmp = *(p - i);
            *(p - i) = *(nizA + i);
            *(nizA + i) = tmp;
        }
    */

   // Preko jednog pokazivaca
   int* p = nizA;
   int tmp = 0;
   for(int i = 0; i < n/2; i++){
        tmp = *(p + n - 1 - i);
        *(p + n - 1 - i) = *(p + i);
        *(p + i) = tmp;
   }

    printf("Elementi niza A: ");
    for(int i=0;i<n;i++ ){
        printf("%d ",nizA[i]);
    }

    return 0;
}