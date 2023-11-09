#include <stdio.h>
#define MAX 40

int main(){
    int n = 0;

    do{
        printf("Unesite paran broj elemenata niza (n<=40): ");
        scanf("%d", &n);
    }while(n % 2 != 0 || n <= 0 || n > MAX);

    int n2 = n/2;
    int suma = 0;
    unsigned char raw[MAX] = {0};
    unsigned char compressed[MAX] = {0};

    printf("Unesite elemente niza:\n");
    for(int i = 0; i < n; i++){
        printf("raw[%d] = ", i);
        scanf("%hhu", &raw[i]);
        suma += raw[i];
    }

    printf("\nSuma elemenata niza je: %d\n\n", suma);

    printf("raw: [");
    for(int i = 0; i < n; i++){
        printf("%hhu", raw[i]);
        if(i != n-1){
            printf(", ");
        }
    }
    printf("]\n\n");

    for(int i = 0; i < n; i++){
        if(i % 2 == 0){
            compressed[i/2] = raw[i] + raw[i+1];
        }
    }

    printf("compressed: [");
    for(int i = 0; i < n2; i++){
        printf("%hhu", compressed[i]);
        if(i != n2-1){
            printf(", ");
        }
    }
    printf("]\n");

    return 0;
}