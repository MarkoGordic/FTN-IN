/*
Napraviti konkurentan program koji obavlja binarnu operaciju XOR (ekskluzivno ili) nad dve ulazne binarne reči (A i B) od po 16 bita. Svaki pojedinačan binarni broj se čuva kao običan int broj i može imati vrednosti 0 ili 1.
Binarna operacija XOR realizuje se po sledećem postupku:

0 XOR 0 = 0
0 XOR 1 = 1
1 XOR 0 = 1
1 XOR 1 = 0

Program treba da obavi operaciju XOR iz 2 zasebne niti, tako da svaka nit obrađuje sopstevnih 8 bita. Niti treba da se izvršavaju konkurentno. Prva nit obrađuje prvih 8 bita prvog i drugog ulaznog vektora a druga nit sledećih 8 bita. Sledi primer:

Vektor A:
0 1 0 1 1 0 0 1  0 1 0 1 0 0 1 1
--- 1. nit ----  --- 2. nit ----

Vektor B:
1 1 0 0 1 1 1 0  0 1 0 1 1 1 0 1
--- 1. nit ----  --- 2. nit ----

Rezultat:
1 0 0 1 0 1 1 1  0 0 0 0 1 1 1 0
--- 1. nit ----  --- 2. nit ----

Potrebno je implementirati dve funkcije:
1) funkciju "izvrsiXOR" koja se nalazi u fajlu logicko_kolo.h
2) funkciju "izracunaj" koja se nalazi u fajlu niti.h

1)
Ulaz u funkciju "izvrsiXOR" su iteratori kroz dva STL vektora - A i B, kao i iterator u rezultujućem vektoru na koji se upisuje rezultat. Pogledati komentar iznad ove funkcije za više detalja.

Test korektnosti funkcije "izvrsiXOR" je dat u fajlu main.cpp, u funkciji "testirajizvrsiXOR".

2)
Funkcija "izracunaj" dobija dva parametra - dva ulazna vektora koji sadrže po 16 binarnih cifara. Ova funkcija treba da pokrene dve konkurentne niti, deleći svakoj po 8 bita od ulaznih vektora. Za funkciju niti treba da se koristi funkcija "izvrsiXOR" koja je realizovana u prvom delu zadatka.

Nakon što niti obave svoje operacije i završe se, funkcija "izracunaj" treba da ukupan rezultat operacije XOR vrati kao svoj rezultat. Važno je da taj vektor ima isti broj elemenata kao i ulazni vektori A i B i da redosled cifara u njemu bude u skladu sa očekivanim (npr da cifra na poziciji 4 odgovara XOR operaciji elemenata na poziciji 4 vektora A i poziciji 4 vektora B).
Test korektnosti funkcije "izracunaj" je dat u main.cpp fajlu, u funkciji "testirajIzracunaj".

*/

#include <iostream>

#include "logicko_kolo.hpp"
#include "niti.hpp"

using namespace std;

void testirajizvrsiXOR() {
    vector<int> a = {0, 1, 0, 1, 1, 0, 0, 1,  0, 1, 0, 1, 0, 0, 1, 1};
    vector<int> b = {1, 1, 0, 0, 1, 1, 1, 0,  0, 1, 0, 1, 1, 1, 0, 1};

    vector<int> rezultat(a.size());
    izvrsiXOR(a.begin(), a.end(), b.begin(), rezultat.begin());

    cout << "Rezultat izvrsavanja funkcije izvrsiXOR():" << endl;

    for (cit it = rezultat.begin(); it != rezultat.end(); it++)
        cout << *it << " ";
    cout << endl;
}

void testirajIzracunaj() {
    vector<int> a = {0, 1, 0, 1, 1, 0, 0, 1,  0, 1, 0, 1, 0, 0, 1, 1};
    vector<int> b = {1, 1, 0, 0, 1, 1, 1, 0,  0, 1, 0, 1, 1, 1, 0, 1};

    vector<int> rezultat = izracunaj(a, b);

    cout << "Rezultat izvrsavanja funkcije izracunaj():" << endl;

    for (cit it = rezultat.begin(); it != rezultat.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
}

int main() {
    testirajizvrsiXOR();
    testirajIzracunaj();

    return 0;
}
