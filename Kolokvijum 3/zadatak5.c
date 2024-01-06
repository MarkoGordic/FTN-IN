#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Vozilo{
    char naziv_bredna[11];
    char naziv_modela[16];
    int cena;
    int zapremina_gepeka;
}Vozilo;

typedef struct node {
    Vozilo podatak;
    struct node* sledeci;
} node;

void zameni(node* a, node* b){
    Vozilo tmp = a->podatak;
    a->podatak = b->podatak;
    b->podatak = tmp;
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

node* kreirajCvor(Vozilo podatak){
    node* novi = (node*)calloc(1, sizeof(node));

    novi->podatak = podatak;
    novi->sledeci = NULL;

    return novi;
}

void dodajNaKraj(node** lista, Vozilo podatak){
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

void dodajNaPocetak(node** lista, Vozilo podatak){
    node* novi = kreirajCvor(podatak);

    if(*lista == NULL){
        *lista = novi;
    }else{
        novi->sledeci = *lista;
        *lista = novi;
    }

}

void ispisiListuUFile(node* lista, char* name){
    if(lista == NULL)
        printf("Lista je prazna.\n");
    else{
        FILE* file = open_file(name, "w");

        while(lista != NULL){
            fprintf(file, "%s %s\n", lista->podatak.naziv_bredna, lista->podatak.naziv_modela);
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

void obrisiCvor(node** lista, int podatak){
    if(*lista == NULL){
        return;
    }

    node* trenutni = *lista;
    if(trenutni->podatak.cena == podatak){
        *lista = (*lista)->sledeci;
        free(trenutni);
        return;
    }
    
    node* prethodni = NULL;
    while(trenutni != NULL && trenutni->podatak.cena != podatak){
        prethodni = trenutni;
        trenutni = trenutni->sledeci;
    }

    if(trenutni == NULL)
        return;

    prethodni->sledeci = trenutni->sledeci;
    free(trenutni);
}

void obrisiDrugiNajjeftiniji(node* lista){
    if(lista == NULL || lista->sledeci == NULL)
        return;

    int prviNajjeftiniji, drugiNajjeftiniji;

    if (lista->podatak.cena < lista->sledeci->podatak.cena) {
        prviNajjeftiniji = lista->podatak.cena;
        drugiNajjeftiniji = lista->sledeci->podatak.cena;
    } else {
        prviNajjeftiniji = lista->sledeci->podatak.cena;
        drugiNajjeftiniji = lista->podatak.cena;
    }

    node* trenutni = lista->sledeci->sledeci;

    while(trenutni != NULL){
        if(trenutni->podatak.cena < prviNajjeftiniji){
            drugiNajjeftiniji = prviNajjeftiniji;
            prviNajjeftiniji = trenutni->podatak.cena;
        } else if (trenutni->podatak.cena < drugiNajjeftiniji && trenutni->podatak.cena != prviNajjeftiniji){
            drugiNajjeftiniji = trenutni->podatak.cena;
        }

        trenutni = trenutni->sledeci;
    }

    if(drugiNajjeftiniji != prviNajjeftiniji)
        obrisiCvor(&lista, drugiNajjeftiniji);
    else
        obrisiCvor(&lista, prviNajjeftiniji);
}

void obrisiDrugiNajskuplji(node* lista){
    if(lista == NULL || lista->sledeci == NULL)
        return;

    int prviNajskuplji, drugiNajskuplji;

    if (lista->podatak.cena > lista->sledeci->podatak.cena) {
        prviNajskuplji = lista->podatak.cena;
        drugiNajskuplji = lista->sledeci->podatak.cena;
    } else {
        prviNajskuplji = lista->sledeci->podatak.cena;
        drugiNajskuplji = lista->podatak.cena;
    }

    node* trenutni = lista->sledeci->sledeci;

    while(trenutni != NULL){
        if(trenutni->podatak.cena > prviNajskuplji){
            drugiNajskuplji = prviNajskuplji;
            prviNajskuplji = trenutni->podatak.cena;
        } else if (trenutni->podatak.cena > drugiNajskuplji && trenutni->podatak.cena != prviNajskuplji){
            drugiNajskuplji = trenutni->podatak.cena;
        }

        trenutni = trenutni->sledeci;
    }

    if(drugiNajskuplji != prviNajskuplji)
        obrisiCvor(&lista, drugiNajskuplji);
    else
        obrisiCvor(&lista, prviNajskuplji);
}

int main(){
    node* glava_komercijalna = NULL;
    node* glava_putnicka = NULL;

    FILE* pfile = open_file("./podaci/vozila.txt", "r");

    Vozilo tmp;
    while(fscanf(pfile, "%s %s %d %d", tmp.naziv_bredna, tmp.naziv_modela, &tmp.cena, &tmp.zapremina_gepeka) == 4){
        if(tmp.zapremina_gepeka >= 600)
            dodajNaKraj(&glava_komercijalna, tmp);
        else
            dodajNaPocetak(&glava_putnicka, tmp);
    }
    fclose(pfile);

    obrisiDrugiNajjeftiniji(glava_komercijalna);
    obrisiDrugiNajskuplji(glava_putnicka);

    ispisiListuUFile(glava_komercijalna, "komercijalna.txt");
    ispisiListuUFile(glava_putnicka, "putnicka.txt");

    unistiListu(glava_komercijalna);
    unistiListu(glava_putnicka);
    return 0;
}