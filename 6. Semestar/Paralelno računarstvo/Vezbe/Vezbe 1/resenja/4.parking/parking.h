#ifndef PARKING_H_INCLUDED
#define PARKING_H_INCLUDED

#include <mutex>
#include <condition_variable>

#include "automobil.h"

using namespace std;

class Parking {
private:
    Automobil& automobil;
    enum Stanje { SLOBODAN, ZAUZET };        // Enumeracija koja predstavlja tip stanja Parkinga.
    Stanje stanje;                           // Promenljva koja sadrži trenutno stanje Parkinga.
    mutex m;                                 // Mutex i uslovna promenljiva neophodni za uslovnu sinhronizaciju.
    condition_variable slobodan;
public:
    Parking(Automobil& a) : automobil(a), stanje(SLOBODAN) {}          // Parking je na početku SLOBODAN.

    // Metoda koju poziva nit koja simulira kretanje automobila kako bi automobil pokušao da se parkira.
    // Ako je parking zauzet, izvršenje ove metode će trajati dok se parking ne oslobodi i auto se parkira.
    //
    // rbr - Redni broj automobila
    //
    // Potrebno je pozvati metodu automobil.ceka kada je parking zauzet i auto mora da čeka.
    // Potrebno je pozvati metodu automobil.parkira kada auto uspe da se parkira.
    void udji(int rbr) {
        unique_lock<mutex> l(m);
        while (stanje == ZAUZET) {               // Provera uslova. MORA se upotrebiti while (umesto if). Ukoliko je Parking zauzet nit mora
            automobil.ceka(rbr);                 // da čeka da se parking oslobodi. NEMA busy waitinga tj. konstantne provere ispunjenosti
            slobodan.wait(l);                    // uslova. Provera se vrši samo po notifikaciji od druge niti.
        }
                                                 // OPTIMALNO iskorišćenje procesora.
        stanje = ZAUZET;                         // Zauzimanje Parkinga (promena stanja).
        automobil.parkira(rbr);
    }

    // Metoda koju poziva nit koja simulira kretanje automobila kada auto izlazi sa parkinga (nakon što je bio parkiran).
    //
    // rbr - Redni broj automobila
    //
    // Potrebno je pozvati metodu automobil.napusta kada auto napušta parking mesto.
    void izadji(int rbr) {
        unique_lock<mutex> l(m);
        stanje = SLOBODAN;                       // Bezuslovna promena stanja na SLOBODAN.
        automobil.napusta(rbr);
        slobodan.notify_one();                   // Notifikacija jedne od niti koje čekaju na promenu stanja.
    }
};

#endif // PARKING_H_INCLUDED
