#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef struct Podatak{
    int dan;
    char naselje[9];
    unsigned int br_zarazenih;
} Podatak;

int main(){
    FILE* pfile;
    pfile = fopen("covid19.txt", "r");

    if(pfile == NULL)
        return -1;

    Podatak* podaci = NULL;
    Podatak tmp;
    char tmp_grad[9];
    int brojac = 0;
    int ukupno_zarazenih = 0;

    while(fscanf(pfile, "%d %s %u", &tmp.dan, tmp.naselje, &tmp.br_zarazenih) == 3){
        if(tmp.dan > 30 || tmp.dan < 1 || tmp.br_zarazenih > 9993)
            continue;
        if(brojac == 120)
            break;

        podaci = (Podatak*)realloc(podaci, sizeof(Podatak) * (brojac + 1));

        for(int i = 0; i < strlen(tmp.naselje); i++)
            if(tmp.naselje[i] == '_')
                tmp.naselje[i] = ' ';

        strcpy(podaci[brojac].naselje, tmp.naselje);
        podaci[brojac].dan = tmp.dan;
        podaci[brojac].br_zarazenih = tmp.br_zarazenih;
        ukupno_zarazenih += tmp.br_zarazenih;
        brojac++;
    }

    fclose(pfile);

    float prosek_zarazenih = (float)ukupno_zarazenih / 30.0;
    printf("prosek: %.1f\n", prosek_zarazenih);

    float devijacija = 0;
    float nova_devijacija = 0;
    int devijacija_index = 0;
    for(int i = 0; i < brojac; i++){
        if(i == 0)
            devijacija = abs(prosek_zarazenih - (float)podaci[0].br_zarazenih);
        
        nova_devijacija = abs(prosek_zarazenih - (float)podaci[i].br_zarazenih);
        if(devijacija > nova_devijacija){
            devijacija = nova_devijacija;
            devijacija_index = i;
        }
    }

    printf("najblizi : %d %s %d\n", podaci[devijacija_index].dan, podaci[devijacija_index].naselje, podaci[devijacija_index].br_zarazenih);

    FILE* pnfile;
    pnfile = fopen("filer.txt", "w");

    if(pnfile == NULL)
        return -1;

    for(int i = 0; i < brojac; i++)
        if(podaci[i].dan % 3 == 0)
            fprintf(pnfile, "%d %s %d\n", podaci[i].dan, podaci[i].naselje, podaci[i].br_zarazenih);

    fclose(pnfile);
    free(podaci);

    return 0;
}