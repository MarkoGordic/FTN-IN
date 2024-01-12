#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Vozacka {
    char broj_vozacke[8];
    char ime[31];
    char prezime[31];
    char oznaka_kategorije;
} Vozacka;

typedef struct node {
    Vozacka podatak;
    struct node* levi;
    struct node* desni;
} node;

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

node* kreirajCvor(Vozacka podatak){
    node* novi = (node*)calloc(1, sizeof(node));

    if(novi == NULL)
        exit(-1);

    novi->podatak = podatak;
    novi->levi = NULL;
    novi->desni = NULL;
}

node* dodajCvor(node* koren, Vozacka podatak){
    if(koren == NULL){
        return kreirajCvor(podatak);
    }

    if(strcmp(podatak.broj_vozacke, koren->podatak.broj_vozacke) > 0){
        koren->desni = dodajCvor(koren->desni, podatak);
    } else if(strcmp(podatak.broj_vozacke, koren->podatak.broj_vozacke) < 0){
        koren->levi = dodajCvor(koren->levi, podatak);
    }

    return koren;
}

node* pronadjiCvor(node* koren, char* broj_vozacke){
    if(koren == NULL || !strcmp(koren->podatak.broj_vozacke, broj_vozacke))
        return koren;

    node* levi = pronadjiCvor(koren->levi, broj_vozacke);
    if(levi != NULL)
        return levi;
    
    node* desni = pronadjiCvor(koren->desni, broj_vozacke);
    if(desni != NULL)
        return desni;

    if(levi == NULL || desni == NULL)
        return NULL;
}

int main(){
    node* koren = NULL;

    FILE* pfile = open_file("./podaci/dozvole.txt", "r");

    bool prvi = true;
    Vozacka tmp;
    while(fscanf(pfile, "%s %s %s %c", tmp.broj_vozacke, tmp.ime, tmp.prezime, &tmp.oznaka_kategorije) == 4){
        if(prvi){
            koren = dodajCvor(koren, tmp);
        } else {
            dodajCvor(koren, tmp);
        }
    }
    fclose(pfile);

    int brojac = 0;
    char unos[8];

    while(brojac != 4){
        printf("Unesite broj vozacke: ");
        scanf("%s", unos);
        while ((getchar()) != '\n');

        node* trazeni = pronadjiCvor(koren, unos);
        if(trazeni == NULL)
            brojac++;
        else{
            printf("%s %s %s %c\n", trazeni->podatak.broj_vozacke, trazeni->podatak.ime, trazeni->podatak.prezime, trazeni->podatak.oznaka_kategorije);
            brojac = 0;
        }
    }

    return 0;
}