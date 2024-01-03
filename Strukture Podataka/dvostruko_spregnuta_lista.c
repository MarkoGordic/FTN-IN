#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int podatak;
    struct node* prethodni;
    struct node* sledeci;
} node;

node* kreirajCvor(int podatak){
    node* novi = (node*)calloc(1, sizeof(node));
    
    novi->podatak = podatak;
    novi->prethodni = NULL;
    novi->sledeci = NULL;

    return novi;
}

void dodajNaKraj(node** lista, int podatak){
    node* novi = kreirajCvor(podatak);

    if(*lista == NULL){
        *lista = novi;
    }
    else{
        node* trenutni = *lista;
        
        while(trenutni->sledeci != NULL)
            trenutni = trenutni->sledeci;

        trenutni->sledeci = novi;
        novi->prethodni = trenutni;
    }
}

void dodajNaPocetak(node** lista, int podatak){
    node* novi = kreirajCvor(podatak);

    if(*lista == NULL)
        *lista = novi;
    else{
        node* glava = *lista;
        *lista = novi;
        glava->prethodni = novi;
        novi->sledeci = glava;
    }
}

void obrisiCvor(node** lista, int podatak){
    if(*lista == NULL)
        return;

    node* trenutni = *lista;
    if(trenutni->podatak == podatak){
        *lista = trenutni->sledeci;
        (*lista)->prethodni = NULL;
        free(trenutni);
        return;
    }

    while(trenutni != NULL && trenutni->podatak != podatak)
        trenutni = trenutni->sledeci;

    if(trenutni == NULL)
        return;

    if(trenutni->sledeci == NULL){
        trenutni->prethodni->sledeci = NULL;
        free(trenutni);
        return;
    }

    trenutni->prethodni->sledeci = trenutni->sledeci;
    trenutni->sledeci->prethodni = trenutni->prethodni;
    free(trenutni);
}

void ispisiListu(node* lista){
    if(lista == NULL)
        printf("Lista je prazna!\n");
    else{
        while(lista->sledeci != NULL){
            printf("%d ", lista->podatak);
            lista = lista->sledeci;
        }
        printf("%d\n", lista->podatak);
    }
}

void unistiListu(node* lista){
    if(lista == NULL)
        return;

    while(lista->sledeci != NULL){
        lista = lista->sledeci;
        free(lista->prethodni);
    }
    free(lista);
}

int main(){
    node* glava = NULL;
    dodajNaKraj(&glava, 5);
    dodajNaKraj(&glava, 8);
    dodajNaPocetak(&glava, 22);
    ispisiListu(glava);
    obrisiCvor(&glava, 8);
    ispisiListu(glava);
    unistiListu(glava);
    return 0;
}