#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Grad {
    char ime[30];
    int broj_stanovnika;
} Grad;

typedef struct node {
    Grad podatak;
    struct node* sledeci;
} node;

void zameni(node* a, node* b){
    Grad tmp = a->podatak;
    a->podatak = b->podatak;
    b->podatak = tmp;
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

void ispisiListuN(node* lista, int n){
    if(lista == NULL)
        printf("Lista je prazna.\n");
    else{
        int brojac = 0;
        while(lista != NULL){
            printf("%s %d\n", lista->podatak.ime, lista->podatak.broj_stanovnika);
            brojac++;

            if(brojac == n)
                return;
            
            lista = lista->sledeci;
        }
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

void dodajUListu(node** lista, Grad podatak){
    if(*lista == NULL)
        dodajNaKraj(lista, podatak);

    node* trenutni = *lista;
    while(trenutni != NULL){
        if(strcmp(trenutni->podatak.ime, podatak.ime) == 0){
            if(trenutni->podatak.broj_stanovnika < podatak.broj_stanovnika){
                trenutni->podatak.broj_stanovnika = podatak.broj_stanovnika;
            }
            return;
        }
        trenutni = trenutni->sledeci;
    }

    dodajNaKraj(lista, podatak);
}

void sortirajListu(node** lista){
    bool zamena;
    node* trenutni = *lista;

    while(trenutni != NULL){
        zamena = false;
        node* unutrasnji = trenutni->sledeci;

        while(unutrasnji != NULL){
            if(trenutni->podatak.broj_stanovnika < unutrasnji->podatak.broj_stanovnika){
                zamena = true;
                zameni(trenutni, unutrasnji);
            }
            unutrasnji = unutrasnji->sledeci;
        }

        if(!zamena)
            return;

        trenutni = trenutni -> sledeci;
    }
}

int main(){
    node* glava = NULL;
    
    FILE* pfile = fopen("./podaci/gradovi.txt", "r");
    Grad tmp;
    while(fscanf(pfile, "%s %d", tmp.ime, &tmp.broj_stanovnika) == 2){
        dodajUListu(&glava, tmp);
    }
    fclose(pfile);

    sortirajListu(&glava);
    ispisiListuN(glava, 5);

    unistiListu(glava);
    return 0;
}