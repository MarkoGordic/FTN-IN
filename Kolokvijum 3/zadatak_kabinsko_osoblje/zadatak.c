#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Let{
    int broj_leta;
    char pozivni_znak[11];
    char oznaka_polazak[4];
    char oznaka_destinacija[4];
    int duzina_leta;
    int maticni1;
    int maticni2;
    int maticni3;
}Let;

typedef struct node {
    Let podatak;
    struct node* levi;
    struct node* desni;
}node;

typedef struct Osoblje{
    int maticni_broj;
    char ime[31];
}Osoblje;

FILE* open_file(char* name, char* mode){
    FILE* pfile;
    pfile = fopen(name, mode);
    
    if(pfile == NULL){
        printf("Neuspesno otvaranje file-a : %s", name);
        exit(-1);
    }
    else
        return pfile;
}

node* kreirajCvor(Let podatak){
    node* novi = (node*)calloc(1, sizeof(node));

    if(novi == NULL)
        exit(-1);

    novi->podatak = podatak;
    novi->levi = NULL;
    novi->desni = NULL;

    return novi;
}

node* dodajCvor(node* koren, Let podatak){
    if(koren == NULL){
        return kreirajCvor(podatak);
    }

    if(podatak.broj_leta > koren->podatak.broj_leta){
        koren->desni = dodajCvor(koren->desni, podatak);
    } else if(podatak.broj_leta < koren->podatak.broj_leta){
        koren->levi = dodajCvor(koren->levi, podatak);
    }

    return koren;
}

void ispisiStabloUFile(node* koren, FILE* pfile){
    if(koren != NULL){
        ispisiStabloUFile(koren->levi, pfile);
        fprintf(pfile, "%d %s %s %s %d %d %d %d\n", koren->podatak.broj_leta, koren->podatak.pozivni_znak, koren->podatak.oznaka_polazak, koren->podatak.oznaka_destinacija, koren->podatak.duzina_leta, koren->podatak.maticni1, koren->podatak.maticni2, koren->podatak.maticni3);
        ispisiStabloUFile(koren->desni, pfile);
    }
}

void unistiStablo(node* koren){
    if(koren == NULL)
        return;

    unistiStablo(koren->levi);
    unistiStablo(koren->desni);

    free(koren);
}

int izracunajBrojMinuta(node* koren, int maticni_broj){
    if(koren == NULL)
        return 0;
    else if(koren->podatak.maticni1 == maticni_broj || koren->podatak.maticni2 == maticni_broj || koren->podatak.maticni3 == maticni_broj)
        return izracunajBrojMinuta(koren->levi, maticni_broj) + koren->podatak.duzina_leta + izracunajBrojMinuta(koren->desni, maticni_broj);
    else
        return izracunajBrojMinuta(koren->levi, maticni_broj) + izracunajBrojMinuta(koren->desni, maticni_broj);
}

int main(){
    node* koren = NULL;

    FILE* pfile = open_file("./podaci/letovi.txt", "r");
    Let tmp;
    bool prvi = true;

    while(fscanf(pfile, "%d %s %s %s %d %d %d %d", &tmp.broj_leta, tmp.pozivni_znak, tmp.oznaka_polazak, tmp.oznaka_destinacija, &tmp.duzina_leta, &tmp.maticni1, &tmp.maticni2, &tmp.maticni3) == 8){
        if(!strcmp(tmp.oznaka_polazak, "BEG")){
            if(prvi){
                koren = dodajCvor(koren, tmp);
                prvi = false;
            } else {
                dodajCvor(koren, tmp);
            }
        }
    }
    fclose(pfile);

    FILE* pnfile = open_file("./podaci/kabinsko_osoblje.txt", "r");
    Osoblje tmp1;
    while(fscanf(pnfile, "%d %s", &tmp1.maticni_broj, tmp1.ime) == 2){
        if(izracunajBrojMinuta(koren, tmp1.maticni_broj) > 15 * 60){
            printf("%s sa matičnim brojem %d je prekoračio broj radnih sati.\n", tmp1.ime, tmp1.maticni_broj);
        }
    }
    fclose(pnfile);

    FILE* nfile = open_file("letovi_filtrirano.txt", "w");
    ispisiStabloUFile(koren, nfile);
    fclose(nfile);

    unistiStablo(koren);
    return 0;
}