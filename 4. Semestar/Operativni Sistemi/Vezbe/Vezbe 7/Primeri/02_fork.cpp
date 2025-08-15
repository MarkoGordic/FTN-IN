#include <iostream>
#include <unistd.h>


int main() {
    pid_t roditelj_pid, dete_pid;

    roditelj_pid = getpid();  // dobavlja se PID procesa koji poziva ovu metodu; u ovom momentu postoji samo roditeljski proces, tako da njegov PID i dobavljamo.

    std::cout << "PID roditelja (originala) PRE poziva fork(): " << roditelj_pid << std::endl;

    dete_pid = fork();  // fork() sistemski poziv podvaja trenutni proces na nacin da se kopira citavo stanje trenutnog procesa

    if (dete_pid < 0) {  // ukoliko je povratna vrednost fork() sistemskog poziva negativna, znaci da je doslo do greske i proces nije podvojen
        std::cerr << "Proces se nije uspesno podvojio." << std::endl;
        exit(1);  // signaliziramo da nas primer nije uspesno uradio zeljeni zadatak.
    } else if (dete_pid == 0) {  // u slucaju uspesnog podvajanja procesa, fork vraca razlicite povrate vrednosti u originalu i kopiji da bi oba znala ko je ko; kopirani proces, tj. dete, dobija nulu (0) kao povratnu vrednost
        std::cout << "DETE: Posao decjeg procesa." << std::endl;
        dete_pid = getpid();  // dete proces dobavlja svoj PID radi ispisa; koristimo dete_pid jer nam ovo polje dalje nije potrebno u detetu; vec smo ga iskoristili da otkrijemo da je trenutni proces dete
        std::cout << "DETE: PID deteta posle poziva fork(): " << dete_pid << std::endl;
    } else {  // roditelj proces dobija kao povratnu vrednost fork() poziva PID deteta (kopiranog procesa) da bi mogao da ga kontrolise.
        roditelj_pid = getpid();  // potvrda da se PID roditelja nije promenio.
        std::cout << "RODITELJ: PID roditelja posle poziva fork(): " << roditelj_pid << std::endl;
        std::cout << "RODITELJ: PID deteta posle poziva fork(): " << dete_pid << std::endl;
    }

    return 0;
}