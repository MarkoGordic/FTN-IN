#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct Asistent {
    char email[101];
    char prezime[31];
    char ime[31];
} Asistent;

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

void prepravi_prezimena(Asistent* asistenti, int brojac){
    char privremeni_znak;

    for(int i = 0; i < brojac; i++){
        if(strlen(asistenti[i].prezime) > 3){
            for(int k = 0; k < 3; k++){
                privremeni_znak = asistenti[i].prezime[strlen(asistenti[i].prezime) - 1];

                for(int j = strlen(asistenti[i].prezime) - 2; j >= 0; j--){
                    asistenti[i].prezime[j + 1] = asistenti[i].prezime[j];
                }

                asistenti[i].prezime[0] = privremeni_znak;
            }
        }

        for(int j = 0; j < strlen(asistenti[i].prezime); j++){
            if(!isdigit(asistenti[i].prezime[j]))
                continue;
            
            switch(asistenti[i].prezime[j]){
                case '0':
                    asistenti[i].prezime[j] = 'o';
                    break;
                case '1':
                    asistenti[i].prezime[j] = 'i';
                    break;
                case '3':
                    asistenti[i].prezime[j] = 'e';
                    break;
                case '5':
                    asistenti[i].prezime[j] = 's';
                    break;
                case '7':
                    asistenti[i].prezime[j] = 't';
                    break;
                default:
                    break;
            }
        }
    }
}

void zameni(Asistent* a1, Asistent* a2){
    Asistent tmp = *a1;
    *a1 = *a2;
    *a2 = tmp;
}

int main(){
    FILE* pfile = open_file("asistenti.txt", "r");

    Asistent* asistenti = NULL;
    Asistent* re_asistenti;
    Asistent tmp;
    bool validan_email;
    int brojac = 0;

    while(fscanf(pfile, "%s %s %s\n", tmp.email, tmp.prezime, tmp.ime) == 3){
        validan_email = false;
        for(int i = 0; i < strlen(tmp.email); i++)
            if(tmp.email[i] == '@')
                validan_email = true;

        if(!validan_email)
            continue;

        re_asistenti = (Asistent*)realloc(asistenti, sizeof(Asistent) * (brojac + 1));
    
        if(re_asistenti == NULL){
            printf("Neuspesna realokacije memorije za asistente!\n");
            return -2;
        }
        else
            asistenti = re_asistenti;

        strcpy(asistenti[brojac].email, tmp.email);
        strcpy(asistenti[brojac].prezime, tmp.prezime);
        strcpy(asistenti[brojac].ime, tmp.ime);
        brojac++;
    }

    fclose(pfile);
    prepravi_prezimena(asistenti, brojac);

    bool zamena;
    for(int i = 0; i < brojac - 1; i++){
        zamena = false;

        for(int j = 0; j < brojac - i - 1; j++){
            if(strcmp(asistenti[j].ime, asistenti[j + 1].prezime) > 0){
                zamena = true;
                zameni(&asistenti[j], &asistenti[j + 1]);
            }
        }
    }

    for(int i = 0; i < brojac; i++)
        printf("%s\n", asistenti[i].email);

    FILE* pnfile = open_file("prepraljeno.txt", "w");
    for(int i = 0; i < brojac; i++){
        fprintf(pnfile, "%s %s %s\n", asistenti[i].email, asistenti[i].prezime, asistenti[i].ime);
    }
    fclose(pnfile);

    int sadrze_prezime = 0;
    int sadrze_ime = 0;
    int sadrze_oba = 0;
    int sadrze_ni_jedan = 0;
    bool ime;
    bool prezime;

    for(int i = 0; i < brojac; i++){
        ime = false;
        prezime = false;

        if(strstr(asistenti[i].email, asistenti[i].ime) != NULL)
            ime = true;
        
        if(strstr(asistenti[i].email, asistenti[i].prezime) != NULL)
            prezime = true;
        
        if(ime && prezime)
            sadrze_oba++;
        else if(ime)
            sadrze_ime++;
        else if(prezime)
            sadrze_prezime++;
        else
            sadrze_ni_jedan++;
    }

    printf("Kolicina mailova koji sadrze: \n");
    printf("    i ime i prezime: %d\n", sadrze_oba);
    printf("    samo ime: %d\n", sadrze_ime);
    printf("    samo prezime: %d\n", sadrze_prezime);
    printf("    ni ime ni prezime: %d\n", sadrze_ni_jedan);

    return 0;
}