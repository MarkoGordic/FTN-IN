#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Poklon {
    int ID;
    char ime[31];
    int dani;
} Poklon;

typedef struct node {
    Poklon podatak;
    struct node* sledeci;
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

node* kreirajCvor(Poklon podatak){
    node* novi = (node*)calloc(1, sizeof(node));

    novi->podatak = podatak;
    novi->sledeci = NULL;

    return novi;
}

void dodajNaKraj(node** lista, Poklon podatak){
    node* novi = kreirajCvor(podatak);

    if(*lista == NULL){
        *lista = novi;
    }else{
        node* trenutni = *lista;
        while(trenutni->sledeci != NULL)
            trenutni = trenutni->sledeci;

        trenutni->sledeci = novi;
    }
}

void obrisiCvor(node** lista, int ID){
    if(*lista == NULL){
        return;
    }

    node* trenutni = *lista;
    if(trenutni->podatak.ID == ID){
        printf("%s ove godine nažalost ipak neće dobiti poklon.\n", trenutni->podatak.ime);
        *lista = (*lista)->sledeci;
        free(trenutni);
        return;
    }
    
    node* prethodni = NULL;
    while(trenutni != NULL && trenutni->podatak.ID != ID){
        prethodni = trenutni;
        trenutni = trenutni->sledeci;
    }

    if(trenutni == NULL)
        return;

    printf("%s ove godine nažalost ipak neće dobiti poklon.\n", trenutni->podatak.ime);
    prethodni->sledeci = trenutni->sledeci;
    free(trenutni);
}

void ispisiListuUFile(node* lista){
    if(lista == NULL)
        printf("Lista je prazna.\n");
    else{
        node* trenutni = lista;
        FILE* file = open_file("popravljeno.txt", "w");
        while(trenutni != NULL){
            fprintf(file, "%d %s %d\n", trenutni->podatak.ID, trenutni->podatak.ime, trenutni->podatak.dani);
            trenutni = trenutni->sledeci;
        }
        fclose(file);
    }
}

void unistiListu(node* lista){
    if(lista == NULL){
        return;
    }

    node* tmp = lista;
    while(lista != NULL){
        lista = lista->sledeci;
        free(tmp);
        tmp = lista;
    }
}

void azurirajPoklon(node *glava, int ID, int noviDani) {
    while (glava != NULL) {
        if (glava->podatak.ID == ID) {
            if (glava->podatak.dani == -999) {
                glava->podatak.dani = noviDani;
            }
            break;
        }
        glava = glava->sledeci;
    }
}

int main() {
    node *glava = NULL;

    FILE *pfile = open_file("./podaci/pokloni.txt", "r");
    Poklon tmp;
    while (fscanf(pfile, "%d %s %d", &tmp.ID, tmp.ime, &tmp.dani) == 3) {
        dodajNaKraj(&glava, tmp);
    }
    fclose(pfile);

    FILE* pnfile = fopen("./podaci/hakovano.txt", "r");
    int tmpID, tmpDani;
    while (fscanf(pnfile, "%d %*f %d", &tmpID, &tmpDani) == 2) {
        if (tmpDani == -1) {
            obrisiCvor(&glava, tmpID);
        } else {
            azurirajPoklon(glava, tmpID, tmpDani);
        }
    }
    fclose(pnfile);

    ispisiListuUFile(glava);
    unistiListu(glava);

    return 0;
}