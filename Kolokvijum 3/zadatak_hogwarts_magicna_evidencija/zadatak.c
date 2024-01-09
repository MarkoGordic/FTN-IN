#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Carobnjak {
    char ID[4];
    char ime[31];
    char prezime[31];
    char dom[21];
    int bodovi;
} Carobnjak;

typedef struct node {
    Carobnjak podatak;
    struct node* sledeci;
} node;

typedef struct Predmet {
    char ID[4];
    char ime[16];
    int kolicina;
} Predmet;

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

node* kreirajCvor(Carobnjak podatak){
    node* novi = (node*)calloc(1, sizeof(node));

    novi->podatak = podatak;
    novi->sledeci = NULL;

    return novi;
}

void dodajNaKraj(node** lista, Carobnjak podatak){
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

void dodajNaPocetak(node** lista, Carobnjak podatak){
    node* novi = kreirajCvor(podatak);

    if(*lista == NULL){
        *lista = novi;
    }else{
        novi->sledeci = *lista;
        *lista = novi;
    }

}

void obrisiCvor(node** lista, char* ID){
    if(*lista == NULL){
        return;
    }

    node* trenutni = *lista;
    if(!strcmp(trenutni->podatak.ID, ID)){
        printf("%s %s ipak nije položio test usled ne posedovanja stapica.\n", trenutni->podatak.ime, trenutni->podatak.prezime);
        *lista = (*lista)->sledeci;
        free(trenutni);
        return;
    }
    
    node* prethodni = NULL;
    while(trenutni != NULL && strcmp(trenutni->podatak.ID, ID)){
        prethodni = trenutni;
        trenutni = trenutni->sledeci;
    }

    if(trenutni == NULL)
        return;

    printf("%s %s ipak nije polozio/la test usled ne posedovanja stapica.\n", trenutni->podatak.ime, trenutni->podatak.prezime);
    prethodni->sledeci = trenutni->sledeci;
    free(trenutni);
}

void ispisiListuPolozili(node* lista){
    if(lista == NULL)
        printf("Lista je prazna.\n");
    else{
        node* trenutni = lista;
        FILE* file = open_file("polozili.txt", "w");
        while(trenutni != NULL){
            if(!strcmp(trenutni->podatak.dom, "Gryffindor")){
                fprintf(file, "%s %s %s %d\n", trenutni->podatak.ID, trenutni->podatak.ime, trenutni->podatak.prezime,  trenutni->podatak.bodovi);
            }
            trenutni = trenutni->sledeci;
        }
        fclose(file);
    }
}

void ispisiListuPali(node* lista){
    if(lista == NULL)
        printf("Lista je prazna.\n");
    else{
        FILE* file = open_file("pali.txt", "w");
        while(lista != NULL){
            fprintf(file, "%s %s %s %d\n", lista->podatak.ID, lista->podatak.ime, lista->podatak.prezime,   lista->podatak.bodovi);
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

int main(){
    node* glava_polozili = NULL;
    node* glava_pali = NULL;

    FILE* pfile = open_file("./podaci/carobnjaci.txt", "r");
    Carobnjak tmp;

    while(fscanf(pfile, "%s %s %s %s %d", tmp.ID, tmp.ime, tmp.prezime, tmp.dom, &tmp.bodovi) == 5){
        if(tmp.bodovi > 50)
            dodajNaPocetak(&glava_polozili, tmp);
        else
            dodajNaKraj(&glava_pali, tmp);
    }
    fclose(pfile);

    FILE* pnfile = open_file("./podaci/predmeti.txt", "r");
    Predmet tmp1;

    while(fscanf(pnfile, "%s %s %d", tmp1.ID, tmp1.ime, &tmp1.kolicina) == 3)
        if(!strcmp(tmp1.ime, "Stapic") && tmp1.kolicina == 0)
            obrisiCvor(&glava_polozili, tmp1.ID);
        
    fclose(pnfile);

    ispisiListuPolozili(glava_polozili);
    ispisiListuPali(glava_pali);

    unistiListu(glava_pali);
    unistiListu(glava_polozili);
    return 0;
}