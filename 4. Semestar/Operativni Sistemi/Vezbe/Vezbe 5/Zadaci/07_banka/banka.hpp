#ifndef BANKA_HPP_INCLUDED
#define BANKA_HPP_INCLUDED

#include "valuta.hpp"
#include "kredit.hpp"

using namespace std;

class Banka {
private:
    Kredit& kredit;
public:

    Banka(Kredit& kr, int inicijalni_dsaldo, int inicijalni_esaldo)
        : kredit(kr) {
        // Prosiriti po potrebi ...
    }

    // Metoda koju poziva nit koja simulira klijenta banke, kada klijent zatraži kredit od banke.
    // Ukoliko banka nema odgovarajuća sredstva kako bi omogućila kredit, metoda će blokirati dok se ta sredstva ne oslobode.
    //
    // rbr - Redni broj klijenta
    // svota - Novčani iznos koji je potreban klijentu
    // valuta - Valuta u kojem je novčani iznos
    //
    // Potrebno je pozvati metodu kredit.ceka kada nema sredstava odgovarajuće valute da se odobri kredit.
    // Potrebno je pozvati metodu kredit.dobio kada se kredit realizuje.
    void uzmi_kredit(int rbr, int svota, Valuta valuta) {
        // Implementirati ...
    }

    // Metoda koju poziva nit koja simulira klijenta banke, kada klijent vrati kredit koji je prethodno uzeo od banke.
    //
    // rbr - Redni broj klijenta
    // svota - Novčani iznos koji je potreban klijentu
    // valuta - Valuta u kojem je novčani iznos
    //
    // Potrebno je pozvati metodu kredit.vratio kada je kredit vraćen.
    void vrati_kredit(int rbr, int svota, Valuta valuta) {
        // Implementirati ...
    }
};

#endif // BANKA_HPP_INCLUDED
