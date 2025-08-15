#ifndef PARKING_HPP_INCLUDED
#define PARKING_HPP_INCLUDED

#include <mutex>
#include <condition_variable>

#include "automobil.hpp"

using namespace std;

class Parking {
    Automobil& automobil;
    mutex m; //propusnica za pristup deljenim resursima u klasi
    condition_variable na_ulazu[3]; //tri reda cekanja - za svaki ulaz po jedan
    bool zauzeto; //da li je mesto zauzeto ili nije
    int aktivan_ulaz; //ulaz na koji treba da udje naredni automobil
public:
    Parking(Automobil& a) : automobil(a), zauzeto(false), aktivan_ulaz(0) {} //posto parking ima jedno mesto koje je inicijalno slobodno. Prvo cemo dozvoliti ulaz sa prvog ulaza

    // Metoda koju poziva nit koja simulira kretanje automobila kada on pokusava da udje na parking.
    // Metoda je blokirajuca - ukoliko nema slobodnog mesta, izvrsenje je u blokadi dok se ono ne oslobodi.
    //
    // rbr  - Redni broj automobila
    // ulaz - Ulaz na koji automobil pokusava da udje
    //
    // Potrebno je pozvati metodu automobil.ceka kada automobil ne moze da pridje parkingu i mora da ceka.
    // Potrebno je pozvati metodu automobil.zauzima kada automobil zauzme parking mesto.
    void udji(int rbr, int ulaz) { //parametar je ulaz na koji se automobil pojavljuje
        unique_lock<mutex> l(m); //zakljucavamo propusnicu pre pristupa deljenim resursima u klasi
        while(zauzeto == true || aktivan_ulaz != ulaz) { //dok god je parking zauzet ili se naredni automobil pusta sa nekog drugog ulaza, automobil mora da ceka
            automobil.ceka(rbr, ulaz);
            na_ulazu[ulaz].wait(l); //uvezivanje u red cekanja na ulazu na koji je automobil dosao
        }
        automobil.zauzima(rbr);
        zauzeto = true; //kada udje na parking, parking je zauzet
        aktivan_ulaz = (aktivan_ulaz+1)%3; //odredjivanje narednog ulaza na koji treba automobil da udje (ide se u krug 0-1-2-0-1-2-0 itd)
    }

    // Metoda koju poziva nit koja simulira kretanje automobila kada on napusta parking na koji je prethodno usao.
    //
    // rbr  - Redni broj automobila
    //
    // Potrebno je pozvati metodu automobil.napusta kada automobil napusti parking mesto.
    void izadji(int rbr) {
        unique_lock<mutex> l(m); //zakljucavamo propusnicu pre pristupa deljenim resursima u klasi
        automobil.napusta(rbr);
        zauzeto = false; //pri napustanju parkinga, mesto se oslobadja
        na_ulazu[aktivan_ulaz].notify_one(); //javimo jednom automobilu u redu iz kojeg pustamo naredni automobil da moze da udje
    }
};

#endif // PARKING_HPP_INCLUDED
