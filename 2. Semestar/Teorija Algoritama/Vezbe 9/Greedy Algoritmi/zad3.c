#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char oznaka;
    int rok;
    int vrednost;
} Posao;

void swap(Posao *a, Posao *b) {
    Posao temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(Posao poslovi[], int n) {
    bool zamena = false;

    for (int i = 0; i < n-1; i++) {
        zamena = false;

        for (int j = 0; j < n-i-1; j++) {
            if (poslovi[j].vrednost < poslovi[j+1].vrednost) {
                zamena = true;
                swap(&poslovi[j], &poslovi[j+1]);
            }
        }

        if(!zamena)
            break;
    }
}

void zakazivanjePoslova(Posao poslovi[], int n) {
    bubbleSort(poslovi, n);

    int maxTermini = 0;
    for (int i = 0; i < n; i++) {
        if (poslovi[i].rok > maxTermini) {
            maxTermini = poslovi[i].rok;
        }
    }

    char zauzetiTermini[maxTermini];
    // Inicijalizujemo niz sa terminima na null karakter
    for (int i = 0; i < maxTermini; i++) {
        zauzetiTermini[i] = '\0';
    }

    int ukupnaVrednost = 0;

    // Popunjavanje niza sa terminima
    for (int i = 0; i < n; i++) {
        for (int j = poslovi[i].rok - 1; j >= 0; j--) {
            if (zauzetiTermini[j] == '\0') {
                zauzetiTermini[j] = poslovi[i].oznaka;
                ukupnaVrednost += poslovi[i].vrednost;
                break;
            }
        }
    }

    printf("Izabrani poslovi : [");
    for (int i = 0; i < maxTermini; i++) {
        if (zauzetiTermini[i] != '\0') {
            printf("%c, ", zauzetiTermini[i]);
        }
    }
    printf("\b\b]\n");
}

int main() {
    Posao poslovi[] = {
        {'a', 2, 100},
        {'b', 1, 19},
        {'c', 2, 27},
        {'d', 1, 25},
        {'e', 3, 15}
    };

    int n = sizeof(poslovi) / sizeof(poslovi[0]);

    zakazivanjePoslova(poslovi, n);

    return 0;
}
