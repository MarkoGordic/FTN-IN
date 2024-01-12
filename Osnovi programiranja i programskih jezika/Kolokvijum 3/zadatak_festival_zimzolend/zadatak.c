#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Izvodjac {
    int ID;
    char ime[51];
    char zanr[21];
}Izvodjac;

typedef struct node {
    Izvodjac podatak;
    struct node* sledeci;
} node;

typedef struct Pesma {
    int ID;
    char ime[51];
    int duzina;
} Pesma;

typedef struct node_pesma {
    Pesma podatak;
    struct node_pesma* sledeci;
} node_pesma;

void zameniPesme(node_pesma* a, node_pesma* b){
    Pesma tmp = a->podatak;
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

node* kreirajCvorIzvodjac(Izvodjac podatak){
    node* novi = (node*)calloc(1, sizeof(node));

    novi->podatak = podatak;
    novi->sledeci = NULL;

    return novi;
}

void dodajNaKrajIzvodjac(node** lista, Izvodjac podatak){
    node* novi = kreirajCvorIzvodjac(podatak);

    if(*lista == NULL){
        *lista = novi;
    }else{
        node* trenutni = *lista;
        while(trenutni->sledeci != NULL)
            trenutni = trenutni->sledeci;

        trenutni->sledeci = novi;
    }
}

node_pesma* kreirajCvorPesma(Pesma podatak){
    node_pesma* novi = (node_pesma*)calloc(1, sizeof(node_pesma));

    novi->podatak = podatak;
    novi->sledeci = NULL;

    return novi;
}

void dodajNaPocetakPesma(node_pesma** lista, Pesma podatak){
    node_pesma* novi = kreirajCvorPesma(podatak);

    if(*lista == NULL){
        *lista = novi;
    }else{
        novi->sledeci = *lista;
        *lista = novi;
    }

}

void sortirajListuPesama(node_pesma** lista){
    bool zamena;
    node_pesma* trenutni = *lista;

    while(trenutni != NULL){
        zamena = false;
        node_pesma* unutrasnji = trenutni->sledeci;

        while(unutrasnji != NULL){
            if(trenutni->podatak.duzina < unutrasnji->podatak.duzina){
                zamena = true;
                zameniPesme(trenutni, unutrasnji);
            }
            unutrasnji = unutrasnji->sledeci;
        }

        if(!zamena)
            return;

        trenutni = trenutni -> sledeci;
    }
}

void ispisiListuPesmeSortirano(node_pesma* lista){
    if(lista == NULL)
        printf("Lista je prazna.\n");
    else{
        FILE* pfile = open_file("pesme_sortirano.txt", "w");
        while(lista){
            int minuti = lista->podatak.duzina / 60;
            int sekunde = lista->podatak.duzina % 60;
            if(sekunde < 10)
                fprintf(pfile, "%d %s %d:0%d\n", lista->podatak.ID, lista->podatak.ime, minuti, sekunde);
            else
                fprintf(pfile, "%d %s %d:%d\n", lista->podatak.ID, lista->podatak.ime, minuti, sekunde);
            
            lista = lista->sledeci;
        }
        fclose(pfile);
    }
}

void ocistiString(char* str){
    for(int i = 0; i < strlen(str); i++)
        if(str[i] == '_')
            str[i] = ' ';
}

void obrisiCvorPesma(node_pesma** lista, char* podatak){
    if(*lista == NULL){
        return;
    }

    node_pesma* trenutni = *lista;
    if(!strcmp(trenutni->podatak.ime, podatak)){
        *lista = (*lista)->sledeci;
        free(trenutni);
        return;
    }
    
    node_pesma* prethodni = NULL;
    while(trenutni != NULL && strcmp(trenutni->podatak.ime, podatak)){
        prethodni = trenutni;
        trenutni = trenutni->sledeci;
    }

    if(trenutni == NULL){
        printf("Pesma za zadatim imenom ne postoji.\n");
        return;
    }

    prethodni->sledeci = trenutni->sledeci;
    free(trenutni);
}

void unistiListuPesme(node_pesma* lista){
    if(lista == NULL){
        return;
    }

    node_pesma* tmp = lista;
    while(lista != NULL){
        lista = lista->sledeci;
        free(tmp);
        tmp = lista;
    }
}

void unistiListuIzvodjaci(node* lista){
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
    node* glava_izvodjaci = NULL;
    node_pesma* glava_pesme = NULL;

    FILE* pfile = open_file("./podaci/izvodjaci.txt", "r");
    Izvodjac tmp;
    
    while(fscanf(pfile, "%d %s %s", &tmp.ID, tmp.ime, tmp.zanr) == 3)
        dodajNaKrajIzvodjac(&glava_izvodjaci, tmp);

    fclose(pfile);

    FILE* pnfile = open_file("./podaci/pesme.txt", "r");
    Pesma tmp1;
    int duzina_liste_pesama = 0;

    while(fscanf(pnfile, "%d %s %d", &tmp1.ID, tmp1.ime, &tmp1.duzina) == 3){
        dodajNaPocetakPesma(&glava_pesme, tmp1);
        duzina_liste_pesama++;
    }

    fclose(pnfile);

    node* trenutni_izvodjaci = glava_izvodjaci;
    while(trenutni_izvodjaci != NULL){
        ocistiString(trenutni_izvodjaci->podatak.ime);
        trenutni_izvodjaci = trenutni_izvodjaci->sledeci;
    }

    node_pesma* trenutni_pesme = glava_pesme;
    while(trenutni_pesme != NULL){
        ocistiString(trenutni_pesme->podatak.ime);
        trenutni_pesme = trenutni_pesme->sledeci;
    }

    sortirajListuPesama(&glava_pesme);
    ispisiListuPesmeSortirano(glava_pesme);

    trenutni_pesme = glava_pesme;
    if(duzina_liste_pesama > 10){
        for(int i = 0; i < duzina_liste_pesama; i++){
            if(i == 0)
                printf("5 NAJDUZIH PESAMA:\n");
            if(i < 5)
                printf("    %d %s %d\n", trenutni_pesme->podatak.ID, trenutni_pesme->podatak.ime, trenutni_pesme->podatak.duzina);

            if(i == duzina_liste_pesama - 6)
                printf("\n5 NAJKRACIH PESAMA:\n");
            if(i > duzina_liste_pesama - 6)
                printf("    %d %s %d\n", trenutni_pesme->podatak.ID, trenutni_pesme->podatak.ime, trenutni_pesme->podatak.duzina);

            trenutni_pesme = trenutni_pesme->sledeci;
        }
    }

    int odabir;
    char pretraga[51];
    do {
        printf("\n(1) : Obrisi pesmu sa zadatim imenom\n");
        printf("(2) : Pretrazi pesme sa zadatim imenom\n");
        printf("(0) : Prekini rad programa\n> ");
        scanf("%d", &odabir);

        switch(odabir){
            case 0:
                break;
            case 1:
                while ((getchar()) != '\n');

                printf("\nUnesite ime pesme: ");
                fgets(pretraga, 51, stdin);
                pretraga[strcspn(pretraga, "\n")] = 0;

                obrisiCvorPesma(&glava_pesme, pretraga);
                printf("Pesma %s je uspesno obrisana.\n", pretraga);
                break;
            case 2:
                while ((getchar()) != '\n');

                printf("\nUnesite ime pesme: ");
                fgets(pretraga, 51, stdin);
                pretraga[strcspn(pretraga, "\n")] = 0;

                trenutni_pesme = glava_pesme;
                while(trenutni_pesme){
                    if(!strcmp(trenutni_pesme->podatak.ime, pretraga))
                        printf("%d %s %d\n", trenutni_pesme->podatak.ID, trenutni_pesme->podatak.ime, trenutni_pesme->podatak.duzina);

                    trenutni_pesme = trenutni_pesme->sledeci;
                }

                break;
        }

        if(odabir == 0)
            break;
    } while(odabir <= 2 && odabir >= 0);

    FILE* nfile = open_file("rok.txt", "w");
    trenutni_izvodjaci = glava_izvodjaci;
    while(trenutni_izvodjaci){
        if(!strcmp(trenutni_izvodjaci->podatak.zanr, "rok")){
            trenutni_pesme = glava_pesme;
            while(trenutni_pesme){
                if(trenutni_izvodjaci->podatak.ID == trenutni_pesme->podatak.ID)
                    fprintf(nfile, "%d %s %d\n", trenutni_pesme->podatak.ID, trenutni_pesme->podatak.ime, trenutni_pesme->podatak.duzina);

                trenutni_pesme = trenutni_pesme->sledeci;
            }
        }

        trenutni_izvodjaci = trenutni_izvodjaci->sledeci;
    }
    fclose(nfile);

    unistiListuPesme(glava_pesme);
    unistiListuIzvodjaci(glava_izvodjaci);

    return 0;
}