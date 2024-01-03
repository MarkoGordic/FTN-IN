#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct node {
    char podatak[31];
    struct node* sledeci;
} node;

node* kreirajCvor(char* podatak){
    node* novi = (node*)calloc(1, sizeof(node));

    strcpy(novi->podatak, podatak);
    novi->sledeci = NULL;

    return novi;
}

void dodajNaKraj(node** lista, char* podatak){
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

void dodajNaPocetak(node** lista, char* podatak){
    node* novi = kreirajCvor(podatak);

    if(*lista == NULL){
        *lista = novi;
    }else{
        novi->sledeci = *lista;
        *lista = novi;
    }
}

void obrisiCvor(node** lista, char* podatak){
    if(*lista == NULL){
        return;
    }

    node* trenutni = *lista;
    if(!strcmp(trenutni->podatak, podatak)){
        *lista = (*lista)->sledeci;
        free(trenutni);
        return;
    }
    
    node* prethodni = NULL;
    while(trenutni != NULL && strcmp(trenutni->podatak, podatak)){
        prethodni = trenutni;
        trenutni = trenutni->sledeci;
    }

    if(trenutni == NULL)
        return;

    prethodni->sledeci = trenutni->sledeci;
    free(trenutni);
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

void izmeniIme(node* lista, char* staroIme, char* novoIme){
    if(lista == NULL)
        return;

    while(lista != NULL){
        if(!strcmp(lista->podatak, staroIme))
            strcpy(lista->podatak, novoIme);

        lista = lista->sledeci;
    }
}

void modifikujImena(node* lista){
    if(lista == NULL)
        return;

    while(lista != NULL){
        for(int i = 0; i < strlen(lista->podatak); i++){
            lista->podatak[i] = tolower(lista->podatak[i]);
        }
        lista->podatak[0] = toupper(lista->podatak[0]);

        lista = lista->sledeci;
    }
}

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

int main(){
    node* glava = NULL;
    
    FILE* pfile = open_file("komande.txt", "r");
    char komanda;
    char staroIme[31], novoIme[31];
    char ime[31];

    while(fscanf(pfile, " %c", &komanda) == 1){
        printf("[DEBUG] : Komanda : %c\n", komanda);
        if(komanda == 'I'){
            fscanf(pfile, "%s %s ", staroIme, novoIme);
            izmeniIme(glava, staroIme, novoIme);
            continue;
        }

        fscanf(pfile, "%s", ime);

        switch(komanda){
            case 'P':
                dodajNaPocetak(&glava, ime);
                break;
            case 'K':
                dodajNaKraj(&glava, ime);
                break;
            case 'B':
                obrisiCvor(&glava, ime);
                break;
        }
    }
    fclose(pfile);

    modifikujImena(glava);
    
    FILE* pnfile = open_file("imena.txt", "w");
    node* trenutni = glava;
    while(trenutni != NULL){
        fprintf(pnfile, "%s\n", trenutni->podatak);
        trenutni = trenutni->sledeci;
    }

    unistiListu(glava);
    return 0;
}