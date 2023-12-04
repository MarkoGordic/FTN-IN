#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Parcela{
    char sifra[6];
    float povrsina;
    float cena;
} Parcela;

void zameni(Parcela *a, Parcela *b){
    Parcela tmp = *a;
    *a = *b;
    *b = tmp;
}

int main(){
    FILE *pfile;
    pfile = fopen("./podaci/parcele.txt", "r");

    if(pfile == NULL)
        return -1;

    Parcela *parcele = NULL;
    int brojac = 0;
    Parcela tmp;

    // Ucitavanje iz fajla
    while(fscanf(pfile, "%5s %f %f", tmp.sifra, &tmp.povrsina, &tmp.cena) == 3){
        parcele = (Parcela *)realloc(parcele, sizeof(Parcela) * (brojac + 1));
        strcpy(parcele[brojac].sifra, tmp.sifra);
        parcele[brojac].povrsina = tmp.povrsina;
        parcele[brojac].cena = tmp.cena;
        brojac++;
    }

    fclose(pfile);
    
    // Sortiranje uz pomoc Bubble Sort-a
    for(int i = 0; i < brojac-1; i++){
        bool zamena = false;

        for(int j = 0; j < brojac - i - 1; j++){
            if((parcele[j].cena / parcele[j].povrsina) < (parcele[j+1].cena / parcele[j+1].povrsina)){
                zameni(&parcele[j], &parcele[j+1]);
                zamena = true;
            }
        }

        if(!zamena)
            break;
    }

    // Upisivanje u fajl
    FILE *pnfile;
    pnfile = fopen("./podaci/najskuplje.txt", "w");

    for(int i = 0; i < 3; i++){
        fprintf(pnfile, "%5s\n", parcele[i].sifra);
    }

    fclose(pnfile);
    free(parcele);

    return 0;
}