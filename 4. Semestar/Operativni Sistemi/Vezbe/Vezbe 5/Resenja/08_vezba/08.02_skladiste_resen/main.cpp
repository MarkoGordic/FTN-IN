// Modelovati Skladiste koje ima dve identicne rampe za istovar robe iz kamiona.
//
// Nosivost kamiona je maksimalno 7 tona.
// Kamioni nose obicnu ili zapaljivu robu.
// Kamioni sa zapaljivom robom imaju prednost pri istovaru.
//
// Kamion koji zeli da ostavi robu u skladistu poziva operaciju istovari().
// Kamion ceka ispred skadista dok jedna od rampi ne postane slobodna.
// Istovar traje onoliko sekundi koliko u kamionu ima tona robe.
//
// Implementirati oznacene metode klase Skladiste u fajlu skladiste.h

#include <thread>
#include <vector>

#include "skladiste.hpp"

using namespace std;

void kamion(Skladiste& s, int kolicina, bool zapaljivo, int rbk) {
    s.istovari(rbk, kolicina, zapaljivo); //istovar robe (uz moguce cekanje ako ispred ima drugih kamiona).
}

const int KAMIONA = 10;

void testirajSve() {
    Kamion k;
    Skladiste s(k);
    thread t[KAMIONA];

    vector<int> tezine = {1, 5, 4, 6, 2, 5, 6, 3, 4, 2};

    for(int i = 0; i < KAMIONA; i++)
        t[i] = thread(kamion, ref(s), tezine[i], i % 2, i + 1);
    for(int i = 0; i < KAMIONA; i++)
        t[i].join();
}

int main() {
    testirajSve();

    return 0;
}
