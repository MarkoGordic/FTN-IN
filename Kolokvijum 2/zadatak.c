#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Student {
    char ime[21];
    char prezime[21];
    unsigned int br_glasova;
} Student;

int main(){
    FILE *pfile;
    pfile = fopen("studenti.txt", "r");

    if(pfile == NULL)
        return -1;

    Student* studenti = NULL;
    Student tmp;
    int brojac = 0;
    while(fscanf(pfile, "%s %s %d", tmp.ime, tmp.prezime, &tmp.br_glasova) == 3){
        studenti = (Student*)realloc(studenti, sizeof(Student) * (brojac + 1));
        strcpy(studenti[brojac].ime, tmp.ime);
        strcpy(studenti[brojac].prezime, tmp.prezime);
        studenti[brojac].br_glasova = tmp.br_glasova;
        brojac++;
    }

    fclose(pfile);

    int indexIme;
    int indexPrezime;
    char tmpSlovo;

    for(int i = 0; i < brojac; i++){
        for(int j = 0; j < strlen(studenti[i].ime); j++){
            if(isupper(studenti[i].ime[j]) != 0){
                indexIme = j;
                break;
            }
        }

        for(int j = 0; j < strlen(studenti[i].prezime); j++){
            if(isupper(studenti[i].prezime[j]) == 0){
                indexPrezime = j;
                break;
            }
        }

        tmpSlovo = studenti[i].ime[indexIme];
        studenti[i].ime[indexIme] = studenti[i].prezime[indexPrezime];
        studenti[i].prezime[indexPrezime] = tmpSlovo;

        for(int j = 0; j < strlen(studenti[i].prezime); j++){
            studenti[i].prezime[j] = tolower(studenti[i].prezime[j]);
        }

        studenti[i].ime[0] = toupper(studenti[i].ime[0]);
        studenti[i].ime[2] = toupper(studenti[i].ime[2]);

        studenti[i].prezime[0] = toupper(studenti[i].prezime[0]);
        studenti[i].prezime[2] = toupper(studenti[i].prezime[2]);
    }

    FILE *pnfile;
    pnfile = fopen("korigovano.txt", "w");

    if(pnfile == NULL)
        return -1;

    int ukupno_glasova = 0;

    for(int i = 0; i < brojac; i++){
        fprintf(pnfile, "%s %s\n", studenti[i].ime, studenti[i].prezime);
        ukupno_glasova += studenti[i].br_glasova;
    }

    float potrebnoGl;
    float osvojeniGl;
    printf("Unesite procenat glasova koji je potreban za prolaz: ");
    scanf("%f", &potrebnoGl);

    for(int i = 0; i < brojac; i++){
        osvojeniGl = (float)studenti[i].br_glasova / ukupno_glasova;

        if(osvojeniGl >= potrebnoGl)
            printf("%s %s %u\n", studenti[i].ime, studenti[i].prezime, studenti[i].br_glasova);
    }

    return 0;
}