#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int podatak;
    struct node* levi;
    struct node* desni;
}node;

node* kreirajCvor(int podatak){
    node* novi = (node*)calloc(1, sizeof(node));

    if(novi == NULL)
        exit(-1);

    novi->podatak = podatak;
    novi->levi = NULL;
    novi->desni = NULL;

    return novi;
}

node* dodajCvor(node* koren, int podatak){
    if(koren == NULL){
        return kreirajCvor(podatak);
    }

    if(podatak > koren->podatak){
        koren->desni = dodajCvor(koren->desni, podatak);
    } else if(podatak < koren->podatak){
        koren->levi = dodajCvor(koren->levi, podatak);
    }

    return koren;
}

node* pronadjiNajmanjiCvor(node* koren){
    node* trenutni = koren;

    while(trenutni && trenutni->levi != NULL){
        trenutni = trenutni->levi;
    }

    return trenutni;
}

node* obrisiCvor(node* koren, int podatak){
    if(koren == NULL)
        return koren;

    if(podatak > koren->podatak)
        koren->desni = obrisiCvor(koren->desni, podatak);
    else if(podatak < koren->podatak)
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
        koren->desni = obrisiCvor(koren->desni, naslednik->podatak);
    }

    return koren;
}

void ispisiStablo(node* koren){
    if(koren != NULL){
        ispisiStablo(koren->desni);
        printf("%d ", koren->podatak);
        ispisiStablo(koren->levi);
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
    koren = dodajCvor(koren, 22);
    dodajCvor(koren, 12);
    dodajCvor(koren, 8);
    dodajCvor(koren, 23);
    dodajCvor(koren, 17);
    dodajCvor(koren, 3);

    ispisiStablo(koren);
    printf("\n");

    obrisiCvor(koren, 22);
    dodajCvor(koren, 7);

    ispisiStablo(koren);
    printf("\n");

    obrisiCvor(koren, 7);

    ispisiStablo(koren);
    printf("\n");

    unistiStablo(koren);
    return 0;
}