#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Student {
    char ime[20];
    char prezime[20];
    int bodovi;
} Student;

int main(){
    FILE* pfile;
    pfile = fopen("r_zadatak1.txt", "r");

    if(pfile == NULL)
        return -1;

    Student* studenti = NULL;
    Student tmp;
    int brojac = 0;

    while(fscanf(pfile, "%s %s %d", tmp.ime, tmp.prezime, &tmp.bodovi) == 3){
        studenti = (Student*)realloc(studenti, sizeof(Student) * (brojac + 1));
        strcpy(studenti[brojac].ime, tmp.ime);
        strcpy(studenti[brojac].prezime, tmp.prezime);
        studenti[brojac].bodovi = tmp.bodovi;
        brojac++;
    }

    fclose(pfile);

    FILE* pnfile;
    int ispis = 0;
    pnfile = fopen("poboljsanje.txt", "w");

    if(pnfile == NULL)
        return -1;

    for(int i = 0; i < brojac; i++){
        if(studenti[i].bodovi != 0){
            float poboljsanje = (float)(20.0 - studenti[i].bodovi)/(float)studenti[i].bodovi * 100;
            studenti[i].ime[0] = tolower(studenti[i].ime[0]);
            studenti[i].prezime[0] = tolower(studenti[i].prezime[0]);
            fprintf(pnfile, "%.2f %s %s\n", poboljsanje, studenti[i].ime, studenti[i].prezime);
        }
        else{
            if(ispis == 0){
                printf("Sledeci studenti ce raditi zadatak 1 u terminu nadoknade:\n");
                ispis = 1;
            }

            for(int k = 0; k < strlen(studenti[i].ime); k++)
                studenti[i].ime[k] = toupper(studenti[i].ime[k]);

            for(int k = 0; k < strlen(studenti[i].prezime); k++)
                studenti[i].prezime[k] = toupper(studenti[i].prezime[k]);

            printf("%s %s\n", studenti[i].ime, studenti[i].prezime);
        }
    }

    fclose(pnfile);
    free(studenti);

    return 0;
}