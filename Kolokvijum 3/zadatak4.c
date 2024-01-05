#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Prognoza {
    char naziv[16];
    float brzina_vetra;
} Prognoza;

typedef struct Grad {
    char naziv[16];
    unsigned int indeks_zagadjenosti;
} Grad;

typedef struct node {
    Grad podatak;
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

node* kreirajCvor(Grad podatak){
    node* novi = (node*)calloc(1, sizeof(node));

    novi->podatak = podatak;
    novi->sledeci = NULL;

    return novi;
}

void dodajNaKraj(node** lista, Grad podatak){
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
        FILE* file = open_file("sutra.txt", "w");

        while(lista != NULL){
            char kategorija[15];

            if(lista->podatak.indeks_zagadjenosti >= 0 && lista->podatak.indeks_zagadjenosti < 50)
                strcpy(kategorija, "ODLICAN");
            else if(lista->podatak.indeks_zagadjenosti >= 50 && lista->podatak.indeks_zagadjenosti < 100)
                strcpy(kategorija, "DOBAR");
            else if(lista->podatak.indeks_zagadjenosti >= 100 && lista->podatak.indeks_zagadjenosti < 150)
                strcpy(kategorija, "PRIHVATLJIV");
            else if(lista->podatak.indeks_zagadjenosti >= 150 && lista->podatak.indeks_zagadjenosti < 200)
                strcpy(kategorija, "ZAGADJEN");
            else if(lista->podatak.indeks_zagadjenosti >= 200)
                strcpy(kategorija, "JAKO_ZAGADJEN");

            fprintf(file, "%s %u %s\n", lista->podatak.naziv, lista->podatak.indeks_zagadjenosti, kategorija);

            lista = lista->sledeci;
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

void azurirajListu(node* lista, Prognoza prognoza){
    if(lista == NULL)
        return;
    
    node* trenutni = lista;
    while(trenutni != NULL){
        if(!strcmp(trenutni->podatak.naziv, prognoza.naziv)){
            if(prognoza.brzina_vetra > 2 && prognoza.brzina_vetra < 5)
                trenutni->podatak.indeks_zagadjenosti *= 0.85;
            else if(prognoza.brzina_vetra > 5)
                trenutni->podatak.indeks_zagadjenosti *= 0.75;

            return;
        }
        
        trenutni = trenutni->sledeci;
    }
}

int main(){
    node* glava = NULL;

    FILE* pfile = open_file("./podaci/gradovi.txt", "r");

    Grad tmp;
    while(fscanf(pfile, "%s %u", tmp.naziv, &tmp.indeks_zagadjenosti) == 2)
        dodajNaKraj(&glava, tmp);

    fclose(pfile);

    FILE* pnfile = open_file("./podaci/prognoza.txt", "r");

    Prognoza tmp1;
    while(fscanf(pnfile, "%s %f", tmp1.naziv, &tmp1.brzina_vetra) == 2)
        azurirajListu(glava, tmp1);

    ispisiListuUFile(glava);
    unistiListu(glava);
    return 0;
}