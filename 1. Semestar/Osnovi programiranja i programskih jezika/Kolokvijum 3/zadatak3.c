#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Limit {
    char oznaka[4];
    unsigned int limit;
} Limit;

typedef struct Ponuda {
    char oznaka[4];
    unsigned int broj_barela;
    float cena;
} Ponuda;

typedef struct node {
    Ponuda podatak;
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

node* kreirajCvor(Ponuda podatak){
    node* novi = (node*)calloc(1, sizeof(node));

    novi->podatak = podatak;
    novi->sledeci = NULL;
    
    return novi;
}

void dodajNaKraj(node** lista, Ponuda podatak){
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

void ispisiListuUFile(node* lista){
    if(lista == NULL)
        printf("Lista je prazna.\n");
    else{
        FILE* file = open_file("uvoz.txt", "w");

        node* trenutni = lista;
        while(trenutni != NULL){
            fprintf(file, "%s %u\n", trenutni->podatak.oznaka, trenutni->podatak.broj_barela);
            trenutni = trenutni->sledeci;
        }

        fclose(file);
    }
}

float izracunajUkupnuCenu(node* lista){
    if(lista == NULL)
        printf("Lista je prazna.\n");
    else{
        float ukupnaCena = 0;

        node* trenutni = lista;
        while(trenutni != NULL){
            ukupnaCena += trenutni->podatak.cena * trenutni->podatak.broj_barela;
            trenutni = trenutni->sledeci;
        }

        return ukupnaCena;
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

void azurirajListu(node* lista, char* oznaka, unsigned int limit){
    if(lista == NULL)
        return;

    node* trenutni = lista;
    while(trenutni != NULL){
        if(!strcmp(trenutni->podatak.oznaka, oznaka) && trenutni->podatak.broj_barela > limit){
            trenutni->podatak.broj_barela = limit;
            return;
        }

        trenutni = trenutni->sledeci;
    }
}

int main(){
    node* glava = NULL;

    FILE* pfile = open_file("./podaci/ponude.txt", "r");

    Ponuda tmp;
    while(fscanf(pfile, "%s %u %f", tmp.oznaka, &tmp.broj_barela, &tmp.cena) == 3)
        dodajNaKraj(&glava, tmp);

    fclose(pfile);

    FILE* pnfile = open_file("./podaci/limit.txt", "r");

    Limit tmp1;
    while(fscanf(pnfile, "%s %u", tmp1.oznaka, &tmp1.limit) == 2)
        azurirajListu(glava, tmp1.oznaka, tmp1.limit);

    fclose(pnfile);

    ispisiListuUFile(glava);
    printf("Ukupna cena uvezene nafte: %.2f\n", izracunajUkupnuCenu(glava));
    unistiListu(glava);

    return 0;
}