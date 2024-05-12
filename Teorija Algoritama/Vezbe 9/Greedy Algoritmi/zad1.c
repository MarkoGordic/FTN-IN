#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 6

typedef struct  {
    int pocetak;
    int kraj;
} Aktivnost;

void bubble_sort(Aktivnost aktivnosti[], int n){
    bool zamena = false;

    for(int i = 0; i < n-1; i++){
        zamena = false;

        for(int j = 0; j < n - i - 1; j++){
            if(aktivnosti[j].kraj > aktivnosti[j+1].kraj){
                Aktivnost tmp = aktivnosti[j];
                aktivnosti[j] = aktivnosti[j+1];
                aktivnosti[j+1] = tmp;

                zamena = true;
            }
        }

        if(!zamena)
            break;
    }
}

int maksimalnoAktivnosti(Aktivnost aktivnosti[], int n){
    bubble_sort(aktivnosti, n);

    int brojac = 1;
    int indeks = 0;
    printf("(%d, %d) ", aktivnosti[indeks].pocetak, aktivnosti[indeks].kraj);

    for(int i = 1; i < n; i++){
        if(aktivnosti[i].pocetak > aktivnosti[indeks].kraj){
            brojac++;
            indeks = i;
            printf("(%d, %d) ", aktivnosti[indeks].pocetak, aktivnosti[indeks].kraj);
        }
    }

    return brojac;
}

int main(){
    Aktivnost aktivnosti[] = {{1,2}, {0,6}, {3,4}, {5,9}, {8,9}, {5,7}};
    
    printf("\nMaksimalan broj aktivnosti koje se ne preklapaju: %d\n", maksimalnoAktivnosti(aktivnosti, MAX));

    return 0;
}