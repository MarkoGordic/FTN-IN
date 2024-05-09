#include <stdio.h>

#define VELICINA 10

typedef struct {
    int kljuc;
    int podatak;
    int status; // 0 - slobodno za upis | 1 - zauzeto | 2 - obrisan
} ELEMENT;

void init(ELEMENT[]);
int hash_function(int); // Hash funkcija za odredjivanje indeksa (parametar je kljuc)
void insert(ELEMENT[], int, int);
int find(ELEMENT[], int);
void delete(ELEMENT[], int);

int main(){
    ELEMENT hash_mapa[VELICINA];

    init(hash_mapa);

    insert(hash_mapa, 5, 10);
    insert(hash_mapa, 7, 20);
    insert(hash_mapa, 5, 30);
    insert(hash_mapa, 1, 40);
    insert(hash_mapa, 2, 50);
    insert(hash_mapa, 3, 60);

    return 0;
}

void init(ELEMENT tabela[]) {
    for(int i = 0; i < VELICINA; i++){
        tabela[i].kljuc = 0;
        tabela[i].podatak = 0;
        tabela[i].status = 0;
    }
}

int hash_function(int kljuc) {
    return kljuc;
}

void insert(ELEMENT tabela[], int kljuc, int podatak){
    int index = hash_function(kljuc);

    if(tabela[index].status == 0){
        tabela[index].kljuc = kljuc;
        tabela[index].podatak = podatak;
        tabela[index].status = 1;
        printf("Dodata vrednost %d sa kljucem %d na poziciju %d\n", podatak, kljuc, index);
    } else if (tabela[index].status == 1){
        printf("Kolizija na poziciji %d\n", index);
    } else if (tabela[index].status == 2){
        // Bio je obrisan element na toj poziciji, pa smo ga sad dodali opet
        tabela[index].kljuc = kljuc;
        tabela[index].podatak = podatak;
        tabela[index].status = 1;
        printf("Dodata vrednost %d sa kljucem %d na poziciju %d\n", podatak, kljuc, index);
    }
}

int find(ELEMENT tabela[], int kljuc){
    int index = hash_function(kljuc);

    if(tabela[index].status == 1) {
        return tabela[index].podatak;
    } else {
        printf("Podatak nije pronadjen!");
        return -1;
    }
}

void delete(ELEMENT tabela[], int kljuc){
    int index = hash_function(kljuc);

    if(tabela[index].status != 2){
        tabela[index].status = 2;
        tabela[index].kljuc = 0;
        tabela[index].podatak = 0;
    } else {
        printf("Podatak je vec obrisan.");
    }
}