// Parking sa 3 ulaza i jednim mestom.
// Na parking automobili ulaze sa ulaza 0, 1 i 2 po round-robin protokolu
// (jedan udje sa prvog, jedan sa drugog, jedan sa treceg i tako u krug).
//
// Automobilu se pri stvaranju prosledjuje vreme (u sekundama) koje se on
// zadrzave na parkingu.
// U programu uvek ima jednak broj automobila na svim ulazima!
//
// Implementirati oznacene metode klase Parking u fajlu parking.h

#include <thread>

#include "parking.hpp"
#include "automobil.hpp"

using namespace std;
using namespace chrono;

void automobil(Parking& p, int ulaz, int ostajem_na_parkingu, int rba) {
    p.udji(rba, ulaz);
    this_thread::sleep_for(seconds(ostajem_na_parkingu));
    p.izadji(rba);
}

const int AUTOMOBILA = 12;

void testirajSve() {
    Automobil a;
    Parking p(a);
    thread t[AUTOMOBILA];

    for(int i = 0; i < AUTOMOBILA; i++)
        t[i] = thread(automobil, ref(p), i % 3, (i % 2) + 1, i + 1); //ulaz na koji automobil ide i broj sekundi koliko se zadrzava zavise od rednog broja automobila. Bitno je da dobijemo na svakom ulazu jednak broj automobila

    for(int i = 0; i < AUTOMOBILA; i++)
        t[i].join();
}

int main() {
    testirajSve();

    return 0;
}
