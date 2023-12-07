/*
Sve ono sto si volela
svojom si rukom srusila
jer u tebi crna reka protice
ponekad bojim se i mene odnece
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Pilot {
    char ime[50];
    char prezime[50];
    int br_godina;
    int br_koncerata;
} Pilot;

int main(){
    FILE *pfile;
    pfile = fopen("./podaci/piloti.txt", "r");

    if(pfile == NULL)
        return -1;

    Pilot tmp;
    Pilot* piloti = NULL;
    int brojac = 0;

    while(fscanf(pfile, "%s %s %d %d", tmp.ime, tmp.prezime, &tmp.br_godina, &tmp.br_koncerata) == 4){
        piloti = (Pilot*)realloc(piloti, sizeof(Pilot) * (brojac + 1));
        strcpy(piloti[brojac].ime, tmp.ime);
        strcpy(piloti[brojac].prezime, tmp.prezime);
        piloti[brojac].br_godina = tmp.br_godina;
        piloti[brojac].br_koncerata = tmp.br_koncerata;
        brojac++;
    }

    fclose(pfile);
    FILE *pnfile;
    pnfile = fopen("./piloti_out.txt","w");

    if(pnfile == NULL)
        return -1;

    float prosecan_br_koncerata;
    for(int i = 0; i < brojac; i++){
        prosecan_br_koncerata = (float)piloti[i].br_koncerata / (float)piloti[i].br_godina;

        if(prosecan_br_koncerata > 7){
            for(int j = 0; j < strlen(piloti[i].ime); j++)
                piloti[i].ime[j] = toupper(piloti[i].ime[j]);
            
            for(int j = 0; j < strlen(piloti[i].prezime); j++)
                piloti[i].prezime[j] = toupper(piloti[i].prezime[j]);
        }
        
        fprintf(pnfile, "%s %s %.2f\n", piloti[i].ime, piloti[i].prezime, prosecan_br_koncerata);
    }

    fclose(pnfile);
    free(piloti);

    return 0;
}