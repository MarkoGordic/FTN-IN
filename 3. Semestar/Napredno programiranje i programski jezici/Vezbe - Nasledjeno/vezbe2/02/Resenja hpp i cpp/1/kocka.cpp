#include "kocka.hpp"

// konstruktor bez parametara
Kocka::Kocka() {
    vrednost = 1;
}

// konstruktor sa parametrima
// nije implementirana logika ako korisnik prosledi vrednost manju od 1 ili vecu od 6
// kocka za igru moze da ima samo vrednosti 1, 2, 3, 4, 5, 6 (broj tackica)
Kocka::Kocka(int i){
   vrednost = i;
}

// konstruktor kopije
Kocka::Kocka(const Kocka &k){
    vrednost = k.vrednost;
}

void Kocka::baci(){
    // formula po kojoj se koristi rand() funkcija je rand()%X+Y
    // gde X predstavlja gornju granicu, a Y donju
    vrednost = rand() % 6 + 1;
}

int Kocka::getVrednost() const{
    return vrednost;
}

