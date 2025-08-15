#pragma GCC diagnostic ignored "-Wwrite-strings"

#include <iostream>
#include <unistd.h>


int main() {
    char *argumenti[] = {"/bin/echo", "Zdravo", "svima", "osim", "Sima!", nullptr};  // postavljanje argumenata za program; uobicajeno u shell-u je prvi parametar sam poziv programa pa ga i mi ukljucujemo na pocetku pre ostalih argumenata; na kraju je nullptr kao znak da nema vise argumenata

    if (execv(argumenti[0], argumenti) == -1) {
        std::cerr << "Doslo je do greske prilikom pokretanja programa!" << std::endl;
        exit(1);
    }

    std::cout << "Sve je u redu i ovu poruku nikada necete videti..." << std::endl;

    return 0;
}
