#ifndef TENISKI_KLUB_HPP_INCLUDED
#define TENISKI_KLUB_HPP_INCLUDED

#include "podaci.hpp"
#include "mec.hpp"

#define MAX_TERENA 30

using namespace std;

class Teniski_klub {                             //Klasa deljenog resursa. Pravi se maksimalno 30 terena, ali ce u realnosti biti samo 3 terena.
private:
    Mec& mec;
public:
    Teniski_klub(Mec& m, int ukupno_terena) : mec(m) {
        // Prosiriti po potrebi ...
    }

    // Metoda koju poziva nit koja simulira mec kako bi izvrsila teniski mec.
    // Metoda je blokirajuca - ako je zeljeni teren zauzet, izvrsenje ce blokirati dok se on ne oslobodi.
    //
    // broj_meca - Redni broj meca
    // na_terenu - Indeks terena na kojem mec treba da se odigra
    //
    // Potrebno je pozvati metodu mec.ceka kada je izabrani teren zauzet i mec mora da ceka.
    // Potrebno je pozvati metodu mec.pocinje kada se isprazni izabrani teren i mec moze da pocne.
    // Potrebno je pozvati metodu mec.zavrsen kada se mec zavrsi i mogu se proslediti izmereni vremenski intervali.
    void odigraj_mec(int broj_meca, int na_terenu) {
        // Implementirati ...
    }
};

#endif // TENISKI_KLUB_HPP_INCLUDED
