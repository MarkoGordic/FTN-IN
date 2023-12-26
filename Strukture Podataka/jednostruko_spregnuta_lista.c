#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int podatak;
    struct node* sledeci;
} node;

node* kreirajCvor(int podatak){
    node* novi = (node*)calloc(1, sizeof(node));

    novi->podatak = podatak;
    novi->sledeci = NULL;

    return novi;
}

void dodajNaKraj(node** lista, int podatak){
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

void dodajNaPocetak(node** lista, int podatak){
    node* novi = kreirajCvor(podatak);

    if(*lista == NULL){
        *lista = novi;
    }else{
        novi->sledeci = *lista;
        *lista = novi;
    }

}

void obrisiCvor(node** lista, int podatak){
    if(*lista == NULL){
        return;
    }

    node* trenutni = *lista;
    if(trenutni->podatak == podatak){
        *lista = (*lista)->sledeci;
        free(trenutni);
        return;
    }
    
    node* prethodni = NULL;
    while(trenutni != NULL && trenutni->podatak != podatak){
        prethodni = trenutni;
        trenutni = trenutni->sledeci;
    }

    if(trenutni == NULL)
        return;

    prethodni->sledeci = trenutni->sledeci;
    free(trenutni);
}

void ispisiListu(node* lista){
    if(lista == NULL)
        printf("Lista je prazna.\n");
    else{
        while(lista->sledeci != NULL){
            printf("%d ", lista->podatak);
            lista = lista->sledeci;
        }
        printf("%d\n", lista->podatak);
    }
}

int main(){
    node* glava = NULL;
    dodajNaKraj(&glava, 1);
    dodajNaKraj(&glava, 5);
    dodajNaKraj(&glava, 6);
    dodajNaPocetak(&glava, 9);
    ispisiListu(glava);
    obrisiCvor(&glava, 9);
    ispisiListu(glava);
    free(glava);
    return 0;
}