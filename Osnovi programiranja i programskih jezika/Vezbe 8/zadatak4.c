#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    FILE *pfile;
    pfile = fopen("./podaci/ulaz.txt", "r");

    if(pfile == NULL)
        return -1;

    int* tekst = NULL;
    int tmp;
    int brojac = 0;

    while((tmp = fgetc(pfile)) != EOF){
        tekst = (int*)realloc(tekst, sizeof(int) * (brojac + 1));
        tekst[brojac] = tmp;
        brojac++;
    }

    fclose(pfile);

    FILE *pnfile;
    pnfile = fopen("izlaz.txt", "w");

    if(pnfile == NULL)
        return -1;

    for(int i = brojac - 1; i >= 0; i--){
        if(tekst[i] != 13)
            fputc((char)tekst[i], pnfile);
    }

    fclose(pnfile);
    free(tekst);

    return 0;
}