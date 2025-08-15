#ifndef SKLADISTE_HPP_INCLUDED
#define SKLADISTE_HPP_INCLUDED

#include <mutex>
#include <condition_variable>
#include <chrono>

#include "kamion.hpp"

using namespace std;

class Skladiste {
private:
    Kamion& kamion;
    mutex m;
    condition_variable normal;
    condition_variable boom;

    
public:
    Skladiste(Kamion& k) : kamion(k) {
        // Prosiriti po potrebi ...
    }

    // Metoda koju poziva nit koja simulira kretanje kamiona kada on pokusava da istovari robu.
    // Metoda je blokirajuca - ako su sve rampe za istovar zauzete, izvrsenje ce blokirati dok se neka ne oslobodi.
    //
    // rbr       - Redni broj kamiona
    // kolicina  - Kolicina robe koja se prevozi (u tonama)
    // zapaljivo - Ukazuje na to da li je roba koja se prevozi zapaljiva (takva roba ima prioritet pri istovaru!)
    //
    // Potrebno je pozvati metodu kamion.ceka kada su rampe zauzete i kamion mora da ceka.
    // Potrebno je pozvati metodu kamion.istovara kada zapocne istovar robe iz kamiona (primetiti da ta metoda zahteva da joj se prosledi indeks rampe na kojoj se obavlja istovar!)
    // Potrebno je pozvati metodu kamion.odlazi kada je kamion zavrsio istovar i odlazi.
    void istovari(int rbr, int kolicina, bool zapaljivo) {
        {
            unique_lock<mutex> l(m);

        }
        this_thread::sleep_for(chrono::milliseconds(kolicina * 1000));
        {
            unique_lock<mutex> l(m);
        }
    }
};

#endif // SKLADISTE_HPP_INCLUDED
