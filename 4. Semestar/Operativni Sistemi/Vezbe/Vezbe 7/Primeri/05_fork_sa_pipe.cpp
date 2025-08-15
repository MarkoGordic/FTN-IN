#include <iostream>
#include <unistd.h>


int main() {
    pid_t dete_pid;
    int tok[2];  // niz za cuvanje deskriptora ulaza i izlaza toka
    int status;

    status = pipe(tok);

    if (status == -1) {
        std::cerr << "Nisam uspeo da napravim tok za preusmerenje ulaza/izlaza." << std::endl;
        exit(1);
    }

    dete_pid = fork();

    if (dete_pid < 0) {  // ukoliko je povratna vrednost fork() sistemskog poziva negativna, znaci da je doslo do greske i proces nije podvojen
        std::cerr << "Proces se nije uspesno podvojio." << std::endl;
        exit(2);  // signaliziramo da nas primer nije uspesno uradio zeljeni zadatak.
    } else if (dete_pid == 0) {  // u slucaju uspesnog podvajanja procesa, fork vraca razlicite povrate vrednosti u originalu i kopiji da bi oba znala ko je ko; kopirani proces, tj. dete, dobija nulu (0) kao povratnu vrednost
        // Dete: stvaralac podataka; slace putem toka tekstualnu poruku roditelju
        close(tok[0]);  // dete je u ovom primeru stvaralac podataka tako da prvo zatvaramo tok citanja za dete

        write(tok[1], "Sportski pozdrav roditelju: ZDRAVO!\n", 37);  // slanje poruke 
    } else {  // roditelj proces dobija kao povratnu vrednost fork() poziva PID deteta (kopiranog procesa) da bi mogao da ga kontrolise.
        close(tok[1]);
        char bafer[15], br_znakova;

        while ((br_znakova = read(tok[0], bafer, 15)) > 0) {
            for (int i = 0; i < br_znakova; i++) 
                std::cout << bafer[i];
        }
    }

    return 0;
}