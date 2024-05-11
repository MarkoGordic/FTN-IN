#include <stdio.h>
#include <string.h>

#define VELICINA 72

typedef struct {
    int kljuc;
    char podatak[15];
    int status; // 0 - slobodno za upis | 1 - zauzeto | 2 - obrisan
} ELEMENT;

void init(ELEMENT[]);
int hash_function(int); // Hash funkcija za odredjivanje indeksa (parametar je kljuc)
void insert(ELEMENT[], int, char[]);
int find(ELEMENT[], int);
void delete(ELEMENT[], int);
void printTable(ELEMENT[]);

int main(){
    ELEMENT hash_mapa[VELICINA];

    init(hash_mapa);

    //       MAPA    kljuc  podatak
    insert(hash_mapa, 43171, "Aleksandra");
    insert(hash_mapa, 6969, "Nikola");
    delete(hash_mapa, 31912);
    insert(hash_mapa, 13531, "Nebojsa");
    insert(hash_mapa, 6969, "Radovan");
    insert(hash_mapa, 31912, "Mladen");
    delete(hash_mapa, 31912);
    insert(hash_mapa, 18131, "Nemanja");

    printTable(hash_mapa);

    return 0;
}

void init(ELEMENT tabela[]) {
    for(int i = 0; i < VELICINA; i++){
        tabela[i].kljuc = 0;
        strcpy(tabela[i].podatak, "\0");
        tabela[i].status = 0;
    }
}

int hash_function(int kljuc) {
    return kljuc % 73;
}

int hash_collision(int index) {
    return index + 2;
}

void printTable(ELEMENT table[]) {
	int i;
	
	for (i=0; i<VELICINA; i++) {
        printf("[%d] : Kljuc: %d | Podatak: %s | Status: %d \n", i, table[i].kljuc, table[i].podatak, table[i].status);
	}

    return;
}

void insert(ELEMENT tabela[], int kljuc, char podatak[]){
    int index = hash_function(kljuc);
    if(index <= 0 && index > VELICINA)
        return;

    if(tabela[index].status == 0){
        tabela[index].kljuc = kljuc;
        strcpy(tabela[index].podatak, podatak);
        tabela[index].status = 1;
        printf("Dodata vrednost %s sa kljucem %d na poziciju %d\n", podatak, kljuc, index);
    } else if (tabela[index].status == 1){
        while (tabela[index].status == 1 && index >= 0 && index < VELICINA) {
            index = hash_collision(index);
        }

        if(index <= 0 && index > VELICINA)
            return;

        tabela[index].kljuc = kljuc;
        strcpy(tabela[index].podatak, podatak);
        tabela[index].status = 1;
        printf("Dodata vrednost %s sa kljucem %d na poziciju %d\n", podatak, kljuc, index);

    } else if (tabela[index].status == 2){
        // Bio je obrisan element na toj poziciji, pa smo ga sad dodali opet
        tabela[index].kljuc = kljuc;
        strcpy(tabela[index].podatak, podatak);
        tabela[index].status = 1;
        printf("Dodata vrednost %s sa kljucem %d na poziciju %d\n", podatak, kljuc, index);
    }
}

// find vraca INDEX u hash mapi a ne podatak
int find(ELEMENT tabela[], int kljuc){
    int index = hash_function(kljuc);
    if(index <= 0 && index > VELICINA)
        return -1;

    if(tabela[index].status == 1 && tabela[index].kljuc == kljuc) {
        return index;
    } else {
        while(tabela[index].kljuc != kljuc && index <= 0 && index > VELICINA){
            if(tabela[index].status == 0){
                printf("Podatak nije pronadjen!");
                return -1;
            }

            index = hash_collision(index);
        }

        if(index <= 0 && index > VELICINA)
            return -1;

        return index;    
    }
}

void delete(ELEMENT tabela[], int kljuc){
    int index = hash_function(kljuc);
    if(index <= 0 && index > VELICINA)
        return;

    if(tabela[index].status != 2){
        tabela[index].status = 2;
        tabela[index].kljuc = 0;
        strcpy(tabela[index].podatak, "\0");
    } else {
        while(tabela[index].kljuc != kljuc && index <= 0 && index > VELICINA){
            if(tabela[index].status == 0){
                printf("Podatak nije pronadjen!");
                return;
            }

            index = hash_collision(index);
        }

        if(index <= 0 && index > VELICINA)
            return;
        
        tabela[index].status = 2;
        tabela[index].kljuc = 0;
        strcpy(tabela[index].podatak, "\0");
    }
}