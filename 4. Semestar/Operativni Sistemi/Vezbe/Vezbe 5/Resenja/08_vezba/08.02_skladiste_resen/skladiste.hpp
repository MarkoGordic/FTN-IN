#ifndef SKLADISTE_HPP_INCLUDED
#define SKLADISTE_HPP_INCLUDED

#include <mutex>
#include <condition_variable>

#include "kamion.hpp"

using namespace std;
using namespace chrono;

class Skladiste {
private:
    Kamion& kamion;
    bool rampa_slobodna[2]; //da li su rampe slobodne - po jedan element niza oznacava stanje svake od rampi
    mutex m; //propusnica za sprecavanje stetnog preplitanja pri pristupu atributima klase
    int zapaljivih_ceka; //broj kamiona koji cekaju da istovare zapaljivu robu
    condition_variable zapaljivi, obicni; //uslovne promenljive za modelovanje redova cekanja kamiona koji prevoze zapaljivu robu i onih koji prevoze obicnu robu
public:
    Skladiste(Kamion& k) : kamion(k), zapaljivih_ceka{0} { rampa_slobodna[0] = true; rampa_slobodna[1] = true; } //inicijalno su obe rampe slobodne i nema kamiona sa zapaljivom robom koji cekaju istovar

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
    void istovari(int rbr, int kolicina, bool zapaljivo) { //kolicina robe koja se istovara i informacija da li je roba zapaljiva
        unique_lock<mutex> l(m); //zakljucavanje propusnica pre pristupa deljenim promenljivim

        while(rampa_slobodna[0] == false && rampa_slobodna[1] == false) { //dok god su obe rampe zauzete, kamion mora da saceka
            if (zapaljivo) { //ako prevozi zapaljivu robu, staje u red kamiona koji prevoze tu vrstu robe
                zapaljivih_ceka++; //ako prevozi zapaljivu robu, evidentiramo da postoji jos jedan takav kamion koji ceka
                kamion.ceka(rbr, kolicina, zapaljivo);
                zapaljivi.wait(l);
                zapaljivih_ceka--;   //kad ne ceka vise smanjuje se broj zapaljivih_ceka
            }
            else {
                kamion.ceka(rbr, kolicina, zapaljivo);
                obicni.wait(l);//ako prevozi obicnu robu, staje u red kamiona koji prevoze tu vrstu robe
            }
        }
        int rampa = rampa_slobodna[0] ? 0 : 1; //kada se jedna od rampi oslobodila, utvrdjuje se koja je to rampa. Na toj rampi ce kamion izvrsiti istovar
        rampa_slobodna[rampa] = false; //zauzima rampu na kojoj ce vrsiti istovar
        kamion.istovara(rbr, kolicina, zapaljivo, rampa);
        l.unlock(); //oslobadjanje propusnice, jer dok je nit u spavanju ne treba sprecavati druge niti da pristupaju deljenim promenljivim
        this_thread::sleep_for(seconds(kolicina)); //simuliranje istovara robe - istovar traje srazmerno kolicini robe
        l.lock(); //ponovo zauzimanje propusnice pre pristupa deljenim promenljivim
        rampa_slobodna[rampa] = true; //oslobadja se rampa na kojoj je kamion zavrsio istovar
        kamion.odlazi(rbr);

        if (zapaljivih_ceka)  //ako ima kamiona koji cekaju da istovare zapaljivu robu, oni imaju prednost, pa se javlja jednom od tih kamiona da izvrsi istovar
            zapaljivi.notify_one();
        else
            obicni.notify_one(); //ako nema kamiona koji cekaju da istovare zapaljivu robu, onda moze jedan od kamiona koji prevoze obicnu robu da izvrsi istovar
    }
};

#endif // SKLADISTE_HPP_INCLUDED
