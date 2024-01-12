#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Radijacija{
    char ID[3];
    float doza_radijacije;
    int broj_stanovnika;
} Radijacija;

typedef struct node {
    Radijacija podatak;
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

node* kreirajCvor(Radijacija podatak){
    node* novi = (node*)calloc(1, sizeof(node));

    if(novi == NULL)
        exit(-1);
    
    novi->podatak = podatak;
    novi->levi = NULL;
    novi->desni = NULL;

    return novi;
}

node* dodajUStablo(node* koren, Radijacija podatak){
    if(koren == NULL)
        return kreirajCvor(podatak);
    
    float nova_kolicina_radijacije = podatak.broj_stanovnika*podatak.doza_radijacije;
    float koren_kolicina_radijacije = koren->podatak.broj_stanovnika*koren->podatak.doza_radijacije;
    
    if(nova_kolicina_radijacije > koren_kolicina_radijacije)
        koren->desni = dodajUStablo(koren->desni, podatak);
    else if(nova_kolicina_radijacije < koren_kolicina_radijacije)
        koren->levi = dodajUStablo(koren->levi, podatak);

    return koren;
}

node* pronadjiNajmanjiCvor(node* koren){
    if(koren == NULL)
        return koren;
    
    while(koren && koren->levi)
        koren = koren->levi;
    
    return koren;
}

node* obrisiCvor(node* koren, float podatak){
    if(koren == NULL)
        return koren;

    float koren_kolicina_radijacije = koren->podatak.broj_stanovnika*koren->podatak.doza_radijacije;

    if(podatak > koren_kolicina_radijacije)
        koren->desni = obrisiCvor(koren->desni, podatak);
    else if(podatak < koren_kolicina_radijacije)
        koren->levi = obrisiCvor(koren->levi, podatak);
    else{
        if(koren->levi == NULL){
            node* tmp = koren->desni;
            free(koren);
            return tmp;
        }
        else if(koren->desni == NULL){
            node* tmp = koren->levi;
            free(koren);
            return tmp;
        }

        node* naslednik = pronadjiNajmanjiCvor(koren->desni);
        koren->podatak = naslednik->podatak;
        koren->desni = obrisiCvor(koren->desni, naslednik->podatak.broj_stanovnika*naslednik->podatak.doza_radijacije);
    }

    return koren;
}

node* pronadjiCvor(node* koren, char* ID){
    if(koren == NULL || !strcmp(koren->podatak.ID, ID))
        return koren;

    node* levi = pronadjiCvor(koren->levi, ID);
    if(levi != NULL)
        return levi;
    
    node* desni = pronadjiCvor(koren->desni, ID);
    if(desni != NULL)
        return desni;

    if(levi == NULL || desni == NULL)
        return NULL;
}

void ispisiStablo(node* koren, FILE* pfile, bool gornja_granica){
    if(koren != NULL){
        ispisiStablo(koren->desni, pfile, gornja_granica);
        
        float doza_radijacije = koren->podatak.doza_radijacije;
        if(gornja_granica)
            doza_radijacije *= 1.1;

        float kolicina_radijacije = koren->podatak.broj_stanovnika*koren->podatak.doza_radijacije;
        char ocena[14];
        if(doza_radijacije < 3)
            strcpy(ocena, "OK");
        else if(doza_radijacije >= 3 && doza_radijacije < 5)
            strcpy(ocena, "NEBEZBEDNO");
        else if(doza_radijacije >= 5)
            strcpy(ocena, "OPASNO");

        fprintf(pfile, "%s %.1f %d %.2f %s\n", koren->podatak.ID, doza_radijacije, koren->podatak.broj_stanovnika, kolicina_radijacije, ocena);
        
        ispisiStablo(koren->levi, pfile, gornja_granica);
    }
}

void unistiStablo(node* koren){
    if(koren == NULL)
        return;

    unistiStablo(koren->levi);
    unistiStablo(koren->desni);

    free(koren);
}

int main(){
    node* koren = NULL;

    FILE* pfile = open_file("./podaci/radijacija.txt", "r");
    bool prvi = true;

    Radijacija tmp;
    while(fscanf(pfile, "%s %f %d", tmp.ID, &tmp.doza_radijacije, &tmp.broj_stanovnika) == 3){
        if(prvi){
            koren = dodajUStablo(koren, tmp);
            prvi = false;
        } else {
            dodajUStablo(koren, tmp);
        }
    }
    fclose(pfile);

    FILE* pnfile = open_file("./podaci/greska.txt", "r");
    char tmp1[3];
    while(fscanf(pnfile, "%s", tmp1) == 1){
        node* trazeni = pronadjiCvor(koren, tmp1);
        obrisiCvor(koren, trazeni->podatak.broj_stanovnika*trazeni->podatak.doza_radijacije);
    }
    fclose(pnfile);

    FILE* nfile = open_file("podaci.txt", "w");
    ispisiStablo(koren, nfile, false);
    fclose(nfile);

    FILE* nnfile = open_file("gornja_granica.txt", "w");
    ispisiStablo(koren, nnfile, true);
    fclose(nnfile);

    unistiStablo(koren);

    return 0;
}