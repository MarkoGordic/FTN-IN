#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Atleticar {
    char oznaka[5];
    char ime[31];
    char prezime[31];
    float duzina_skoka;
} Atleticar;

typedef struct node {
    Atleticar podatak;
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

node* kreirajCvor(Atleticar podatak){
    node* novi = (node*)calloc(1, sizeof(node));

    novi->podatak = podatak;
    novi->sledeci = NULL;

    return novi;
}

void dodajNaKraj(node** lista, Atleticar podatak){
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

void obrisiCvor(node** lista, char* oznaka){
    if(*lista == NULL){
        return;
    }

    node* trenutni = *lista;
    if(!strcmp(trenutni->podatak.oznaka, oznaka)){
        *lista = (*lista)->sledeci;
        free(trenutni);
        return;
    }
    
    node* prethodni = NULL;
    while(trenutni != NULL && strcmp(trenutni->podatak.oznaka, oznaka)){
        prethodni = trenutni;
        trenutni = trenutni->sledeci;
    }

    if(trenutni == NULL)
        return;

    prethodni->sledeci = trenutni->sledeci;
    free(trenutni);
}

void upisiListuUIzlazniFile(node* lista, char* oznaka){
    if(lista == NULL)
        printf("Lista je prazna.\n");
    else{
        FILE* pfile = open_file("rezultati.txt", "w");

        while(lista != NULL){
            if(!strcmp(lista->podatak.oznaka, oznaka)){
                for(int i = 0; i < strlen(lista->podatak.ime); i++)
                    lista->podatak.ime[i] = toupper(lista->podatak.ime[i]);

                for(int i = 0; i < strlen(lista->podatak.prezime); i++)
                    lista->podatak.prezime[i] = toupper(lista->podatak.prezime[i]);
            }

            fprintf(pfile, "%s %s %s %.2f\n", lista->podatak.oznaka, lista->podatak.ime, lista->podatak.prezime, lista->podatak.duzina_skoka);
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

int main(){
    node* glava = NULL;
    FILE* pfile = open_file("./podaci/skokovi.txt", "r");

    Atleticar tmp;
    while(fscanf(pfile, "%s %s %s %f", tmp.oznaka, tmp.ime, tmp.prezime, &tmp.duzina_skoka) == 4){
        dodajNaKraj(&glava, tmp);
    }
    fclose(pfile);

    FILE* pnfile = fopen("./podaci/doping.txt", "r");
    char oznaka_tmp[5];
    while(fscanf(pnfile, "%s", oznaka_tmp) == 1){
        obrisiCvor(&glava, oznaka_tmp);
    }
    fclose(pnfile);

    node* trenutni = glava;
    if(glava == NULL){
        return 0;
    }

    float max_skok = glava->podatak.duzina_skoka;
    strcpy(oznaka_tmp, glava->podatak.oznaka);
    while(trenutni != NULL){
        if(trenutni->podatak.duzina_skoka > max_skok){
            max_skok = trenutni->podatak.duzina_skoka;
            strcpy(oznaka_tmp, trenutni->podatak.oznaka);
        }

        trenutni = trenutni->sledeci;
    }

    upisiListuUIzlazniFile(glava, oznaka_tmp);
    unistiListu(glava);

    return 0;
}