#ifndef PARKING_H_INCLUDED
#define PARKING_H_INCLUDED

#include <mutex>

#include "automobil.h"

using namespace std;

class Parking {
private:
    Automobil& automobil;
    enum Stanje { SLOBODAN, ZAUZET };        //Enumeracija koja predstavlja tip stanja Parkinga.
    Stanje stanje;                           //Promenljva koja sadrzi trenutno stanje Parkinga.
    mutex m;                                 //Mutex i uslovna promenljiva neophodni za uslovnu sinhronizaciju.
public:
    Parking(Automobil& a) : automobil(a), stanje(SLOBODAN) {}          //Parking je na pocetku SLOBODAN.

    // Metoda koju poziva nit koja simulira kretanje automobila kako bi automobil pokusao da se parkira.
    // Ako je parking zauzet, izvrsenje ove metode ce trajati dok se parking ne oslobodi i auto se parkira.
    //
    // rbr - Redni broj automobila
    //
    // Potrebno je pozvati metodu automobil.ceka kada je parking zauzet i auto mora da ceka.
    // Potrebno je pozvati metodu automobil.parkira kada auto uspe da se parkira.
    void udji(int rbr) {                         //Funkcija koju pozivaju niti automobila na pocetku rada.
        if (stanje == ZAUZET) {
            unique_lock<mutex> lock(m);
            automobil.ceka(rbr);
        }

        while (true) {                           //Konstantna provera ispunjenosti uslova. Izrazito OPTERECUJE procesor (tzv. busy
            unique_lock<mutex> lock(m);          //waiting. Izrazito NEOPTIMALAN nacin provere uslova.
            if (stanje == SLOBODAN) {            //Provera zauzetosti Parkinga. Tek ukoliko je slobodan petlja se napusta (break).
                stanje = ZAUZET;                 //Zauzimanje Parkinga (promena stanja).
                automobil.parkira(rbr);
                break;
            }
        }
    }

    // Metoda koju poziva nit koja simulira kretanje automobila kada auto izlazi sa parkinga (nakon sto je bio parkiran).
    //
    // rbr - Redni broj automobila
    //
    // Potrebno je pozvati metodu automobil.napusta kada auto napusta parking mesto.
    void izadji(int rbr) {                       //Funkcija koju pozivaju niti automobila na kraju rada.
        unique_lock<mutex> l(m);
        stanje = SLOBODAN;                       //Bezuslvna promena stanja na slobodan. Ovo je izvodljivo jer automobil koji je
        automobil.napusta(rbr);                  //vec na Parkingu (izlazi) nema potrebe da pita da li je Parking zauzet jer on
    }                                            //sam zauzima taj Parking. Tj. Parking je SIGURNO zauzet.

};

#endif // PARKING_H_INCLUDED
