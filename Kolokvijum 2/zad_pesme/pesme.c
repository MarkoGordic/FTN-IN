#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct Pesma{
    char ime[31];
    char autor[31];
    char duzina[6];
} Pesma;

FILE* open_file(char* name, char* mode){
    FILE* pfile;
    pfile = fopen(name, mode);

    if(pfile == NULL){
        printf("Neuspesno otvaranje datoteke %s.\n", name);
        exit(-1);
    }
    else
        return pfile;
}

void koriguj(Pesma* pesme, int brojac){
    for(int i = 0; i < brojac; i++){
        for(int j = 0; j < strlen(pesme[i].ime); j++){
            if(isalpha(pesme[i].ime[j])){
                if(j == 0 && !isupper(pesme[i].ime[j]))
                    pesme[i].ime[j] = toupper(pesme[i].ime[j]);
                else if(j != 0 && isupper(pesme[i].ime[j]))
                    pesme[i].ime[j] = tolower(pesme[i].ime[j]);
            }
            else{
                if(pesme[i].ime[j] == '_')
                    pesme[i].ime[j] = ' ';
            }
        }

        for(int j = 0; j < strlen(pesme[i].autor); j++){
            if(isalpha(pesme[i].autor[j])){
                if(j == 0 && !isupper(pesme[i].autor[j]))
                    pesme[i].ime[j] = toupper(pesme[i].autor[j]);
                else if(j != 0 && isupper(pesme[i].ime[j]))
                    pesme[i].ime[j] = tolower(pesme[i].autor[j]);
            }
            else{
                if(pesme[i].autor[j] == '_')
                    pesme[i].autor[j] = ' ';
            }
        }
    }
}

void zameni(Pesma* p1, Pesma* p2){
    Pesma tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

int main(){
    FILE* pfile = open_file("pesme.txt", "r");

    Pesma* pesme = NULL;
    Pesma* r_pesme = NULL;
    Pesma tmp;
    int brojac = 0;

    while(fscanf(pfile, "%s %s %s", tmp.ime, tmp.autor, tmp.duzina) == 3){
        r_pesme = (Pesma*)realloc(pesme, sizeof(Pesma) * (brojac + 1));
        
        if(r_pesme == NULL){
            printf("Neuspesno realociranje memorije!\n");
            return -2;
        }
        else
            pesme = r_pesme;

        strcpy(pesme[brojac].ime, tmp.ime);
        strcpy(pesme[brojac].autor, tmp.autor);
        strcpy(pesme[brojac].duzina, tmp.duzina);
        brojac++;
    }

    fclose(pfile);

    koriguj(pesme, brojac);

    for(int i = 0; i < brojac; i++){
        for(int j = 0; j < strlen(pesme[i].ime); j++){
            if(isalpha(pesme[i].ime[j])){
                if(j == 0 && !isupper(pesme[i].ime[j]))
                    pesme[i].ime[j] = toupper(pesme[i].ime[j]);
                else if(j == strlen(pesme[i].ime) - 1 && islower(pesme[i].ime[j]))
                    pesme[i].ime[j] = toupper(pesme[i].ime[j]);
                else if(islower(pesme[i].ime[j]) && (pesme[i].ime[j - 1] == ' ' || pesme[i].ime[j + 1] == ' '))
                    pesme[i].ime[j] = toupper(pesme[i].ime[j]);
                else if(isupper(pesme[i].ime[j] && !pesme[i].ime[j - 1] == ' ' && !pesme[i].ime[j + 1] == ' '))
                    pesme[i].ime[j] = tolower(pesme[i].ime[j]);
            }
        }

        for(int j = 0; j < strlen(pesme[i].autor); j++){
            if(isalpha(pesme[i].autor[j])){
                if(j == 0 && !isupper(pesme[i].autor[j]))
                    pesme[i].autor[j] = toupper(pesme[i].autor[j]);
                else if(islower(pesme[i].autor[j]) && pesme[i].autor[j - 1] == ' ')
                    pesme[i].autor[j] = toupper(pesme[i].autor[j]);
                else if(isupper(pesme[i].autor[j] && !pesme[i].autor[j - 1] == ' '))
                    pesme[i].autor[j] = tolower(pesme[i].autor[j]);
            }
        }
    }

    FILE* pnfile = open_file("ispravljeno.txt", "w");

    for(int i = 0; i < brojac; i++)
        fprintf(pnfile, "%s %s %s\n", pesme[i].ime, pesme[i].autor, pesme[i].duzina);

    fclose(pnfile);

    koriguj(pesme, brojac);

    bool zamena;
    for(int i = 0; i < brojac - 1; i++){

        zamena = false;
        for(int j = 0; j < brojac - i - 1; j++){
            if(pesme[j].ime[0] > pesme[j + 1].ime[0]){
                zameni(&pesme[j], &pesme[j + 1]);
                zamena = true;
            }
        }

        if(!zamena)
            break;
    }

    FILE* pnfile2 = open_file("sortirano.txt", "w");

    int vreme;
    for(int i = 0; i < brojac; i++){
        vreme = 0;
        vreme += (int)(pesme[i].duzina[0] - '0') * 10 * 60;
        vreme += (int)(pesme[i].duzina[1] - '0') * 60;
        vreme += (int)(pesme[i].duzina[3] - '0') * 10;
        vreme += (int)(pesme[i].duzina[4] - '0');
        fprintf(pnfile2, "%s %s %d\n", pesme[i].ime, pesme[i].autor, vreme);
    }

    fclose(pnfile2);

    char odabir;
    do{
        printf("Da li zelite da pretrazite pesme po imenu autora ili imenu pesme? (i/a)\n> ");
        scanf("%c", &odabir);

        while ((getchar()) != '\n');

        if(odabir != 'i' && odabir != 'a')
            printf("Neispravan unos!\n");
    }while(odabir != 'i' && odabir != 'a');

    char unos[31];
    if(odabir == 'a'){
        printf("Unesite ime zeljenog autora: \n> ");
        fgets(unos, 30, stdin);
    }else{
        printf("Unesite zeljeno ime pesme: \n> ");
        fgets(unos, 30, stdin);
    }

    for(int i = 0; i < strlen(unos); i++){
        if(isalpha(unos[i])){
            if(i == 0 && !isupper(unos[i]))
                unos[i] = toupper(unos[i]);
            else if(islower(unos[i]) && unos[i - 1] == ' ')
                unos[i] = toupper(unos[i]);
            else if(isupper(unos[i] && !unos[i - 1] == ' '))
                unos[i] = tolower(unos[i]);
        }else{
            if(unos[i] == '\n')
                unos[i] = '\0';
        }
    }

    if(odabir == 'a'){
        printf("Pesme autora '%s' :\n", unos);
        for(int i = 0; i < brojac; i++){
            if(strcmp(unos, pesme[i].autor) == 0)
                printf("    %s %s %s\n", pesme[i].ime, pesme[i].autor, pesme[i].duzina);
        }
    }else{
        printf("Pesme sa nazivom '%s' :\n", unos);
        for(int i = 0; i < brojac; i++){
            if(strcmp(unos, pesme[i].ime) == 0)
                printf("    %s %s %s\n", pesme[i].ime, pesme[i].autor, pesme[i].duzina);
        }
    }

    free(pesme);

    return 0;
}