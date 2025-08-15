/*
Napraviti konkurentan program koji sabira korespondentne elemente vektora A i B i zbirove smešta na odgovarajuće pozicije vektora C.
Korespondentni elementi su elementi na istim pozicijama -- npr. sabiraju se element na poziciji 0 vektora A i element na poziciji 0 vektora B i na poziciju 0 rezultujućeg vektora C se postavlja rezultat tog sabiranja. Proces se nastavlja sa pozicijom 1 i tako do kraja ulaznih vektora.
Konkurentnost ovog rešenja podrazumeva da sabiranje svakog para elemenata treba da obavlja posebna nit.

Ulazni vektori A i B imaju isti broj elemenata. Rezultujući vektor C treba kreirati tako da sadrži isti broj elemenata koliko imaju i vektori A i B.

Potrebno je implementirati dve funkcije:
1) funkciju "saberiPar" koja se nalazi u fajlu sabiranje.h
2) funkciju "izracunaj" koja se nalazi u fajlu niti.h

1)
Ulaz u funkciju "saberiPar" su iteratori kroz dva STL vektora - A i B, kao i iterator u rezultujućem vektoru na koji se upisuje rezultat.

Test korektnosti funkcije "saberiPar" je dat u fajlu main.cpp, u funkcijama "testirajSaberiParPozicija0" i "testirajSaberiParPozicija3". Ulaz ove dve funkcije su vektori A i B:
Vektor A:
0 4 3 3 0 1 2 7 0 1

Vektor B:
1 0 2 6 9 7 5 1 8 8

Pri čemu prva funkcija ("testirajSaberiParPozicija0") testira sabiranje elemenata na poziciji 0, dok druga funkcija ("testirajSaberiParPozicija3") testira sabiranje elemenata na poziciji 3.

2)
Funkcija "izracunaj" dobija dva parametra - dva ulazna vektora koji sadrže neki broj cifara. Ova funkcija treba da pokrene onoliko konkurentnih niti koliko je elemenata u ulaznim vektorima. Svaka nit treba da obrađuje po jedan par elemenata i za sabiranje treba da koristi funkciju "saberiPar" koja je realizovana u prvom delu zadatka. Sledi primer:

Vektor A:
0 4 3 3 0 1 2 7 0 1

Vektor B:
1 0 2 6 9 7 5 1 8 8

(isti ulazni vektori kao u pređašnjim primerima)

Rezultat (vektor C):
1 4 5 9 9 8 7 8 8 9

Nakon što niti obave svoje operacije i završe se, funkcija "izracunaj" treba da ukupan rezultat sabiranja (vektor C) vrati kao svoj rezultat. Važno je da taj vektor ima isti broj elemenata kao i ulazni vektori A i B i da redosled cifara u njemu bude u skladu sa očekivanim (npr da cifra na poziciji 4 odgovara zbiru elemenata na poziciji 4 vektora A i poziciji 4 vektora B).

Test korektnosti funkcije "izracunaj" je dat u main.cpp fajlu, u funkciji "testirajIzracunaj".

*/

#include <iostream>

#include "sabiranje.hpp"
#include "niti.hpp"

using namespace std;

// Sabiraju se elementi na poziciji 0 vektora A i poziciji 0 vektora B
void testirajSaberiParPozicija0() {
    vector<int> a = {0, 4, 3, 3, 0, 1, 2, 7, 0, 1};
    vector<int> b = {1, 0, 2, 6, 9, 7, 5, 1, 8, 8};

    vector<int> rezultat(a.size());
    saberiPar(a.begin(), b.begin(), rezultat.begin());

    cout << "Rezultat izvrsavanja funkcije saberiPar() za poziciju 0:" << endl;

    for (cit it = rezultat.begin(); it != rezultat.end(); it++)
        cout << *it << " ";
    cout << endl;
}

// Sabiraju se elementi na poziciji 0 vektora A i poziciji 0 vektora B
void testirajSaberiParPozicija3() {
    vector<int> a = {0, 4, 3, 3, 0, 1, 2, 7, 0, 1};
    vector<int> b = {1, 0, 2, 6, 9, 7, 5, 1, 8, 8};

    vector<int> rezultat(a.size());
    saberiPar(a.begin() + 3, b.begin() + 3, rezultat.begin() + 3);

    cout << "Rezultat izvrsavanja funkcije saberiPar() za poziciju 3:" << endl;

    for (cit it = rezultat.begin(); it != rezultat.end(); it++)
        cout << *it << " ";
    cout << endl;
}

void testirajIzracunaj() {
    vector<int> a = {0, 4, 3, 3, 0, 1, 2, 7, 0, 1};
    vector<int> b = {1, 0, 2, 6, 9, 7, 5, 1, 8, 8};

    vector<int> rezultat = izracunaj(a, b);

    cout << "Rezultat izvrsavanja funkcije izracunaj():" << endl;

    for (cit it = rezultat.begin(); it != rezultat.end(); it++)
        cout << *it << " ";
    cout << endl;
}

int main() {
    testirajSaberiParPozicija0();
    testirajSaberiParPozicija3();
    // Otkomentarisati kada implementirate funkciju "izracunaj":
    //testirajIzracunaj();

    return 0;
}
