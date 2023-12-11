#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct Anime {
    char ime[101];
    float ocena;
    unsigned int br_epizoda;
    char izvor[11];
} Anime;

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

void formatiranje(Anime* niz, int brojac){
    for(int i = 0; i < brojac; i++){
        for(int j = 0; j < strlen(niz[i].ime); j++){
            if(isalpha(niz[i].ime[j])){
                if(j == 0 && !isupper(niz[i].ime[j]))
                    niz[i].ime[j] = toupper(niz[i].ime[j]);
                else if(j != 0 && !islower(niz[i].ime[j]))
                    niz[i].ime[j] = tolower(niz[i].ime[j]);
            }
            else if(niz[i].ime[j] == '*')
                niz[i].ime[j] = ' ';
        }
    }
}

void zameni(Anime* a1, Anime* a2){
    Anime tmp = *a1;
    *a1 = *a2;
    *a2 = tmp;
}

int main(){
    FILE* pfile = open_file("ani.me", "r");

    Anime* anime = NULL;
    Anime* anime_r = NULL;
    Anime tmp;
    int brojac = 0;

    while(fscanf(pfile, "%s %f %u %s", tmp.ime, &tmp.ocena, &tmp.br_epizoda, tmp.izvor) == 4){
        if(tmp.ocena < 0 || tmp.ocena > 10)
            continue;

        anime_r = (Anime*)realloc(anime, sizeof(Anime) * (brojac + 1));

        if(anime_r == NULL){
            printf("Realokcaija memorije nije uspela!\n");
            free(anime);
            return -2;
        }
        else
            anime = anime_r;

        strcpy(anime[brojac].ime, tmp.ime);
        anime[brojac].ocena = tmp.ocena;
        anime[brojac].br_epizoda = tmp.br_epizoda;
        strcpy(anime[brojac].izvor, tmp.izvor);
        brojac++;
    }
    
    fclose(pfile);

    formatiranje(anime, brojac);

    char odabir;
    do{
        printf("Da li zelite da filtrirate originale samo od filmova? (d/n)\n> ");
        scanf("%c", &odabir);

        if(odabir != 'd' && odabir != 'n')
            printf("Neispravan unos!\n");
    }while(odabir != 'd' && odabir != 'n');

    FILE* pnfile;
    pnfile = fopen("originali.txt", "w");

    if(odabir == 'd'){
        for(int i = 0; i < brojac; i++)
            if(!strcmp(anime[i].izvor, "originalan") && anime[i].br_epizoda == 1){
                fprintf(pnfile, "%s %u\n", anime[i].ime, anime[i].br_epizoda);
            }
    }
    else{
        for(int i = 0; i < brojac; i++)
            if(!strcmp(anime[i].izvor, "originalan"))
                fprintf(pnfile, "%s %u\n", anime[i].ime, anime[i].br_epizoda);
    }

    bool zamena;
    for(int i = 0; i < brojac - 1; i++){
        zamena = false;

        for(int j = 0; j < brojac - i - 1; j++){
            if((anime[j].ocena * anime[j].br_epizoda) < (anime[j + 1].ocena * anime[j + 1].br_epizoda)){
                zameni(&anime[j], &anime[j + 1]);
                zamena = true;
            }
        }

        if(!zamena)
            break;
    }

    printf("\nTOP 5 ANIMEA : \n");
    for(int i = 0; i < 5; i++)
        printf("    %.1f %s\n", anime[i].ocena, anime[i].ime);

    fclose(pnfile);
    free(anime);

    return 0;
}