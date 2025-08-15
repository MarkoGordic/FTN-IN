/*
Napraviti konkurentni program koji u poseboj niti vrši obrtanje redosleda elemenata u ulaznoj listi (listi celobrojnih vrednosti).

Na primer, ako je ulazna lista definisana ovako:
1, 2, 3, 5, 4

Rezultat obrtanja redosleda elemenata treba da izgleda ovako:
4, 5, 3, 2, 1

Potrebno je implementirati dve funkcije:
1) funkciju "obrniRedosled" koja se nalazi u fajlu obrtanje.h
2) funkciju "izracunaj" koja se nalazi u fajlu niti.h

1)
Ulaz u funkciju "obrniRedosled" su dve liste - ulazna i izlazna. Ulazna lista je ona čiji se elementi samo čitaju (ona se ne sme menjati!) i koji se u obrnutom redosledu upisuju u izlaznu listu.

Test korektnosti funkcije "obrniRedosled" je dat u fajlu main.cpp, u funkciji "testirajObrniRedosled".

2)
Funkcija "izracunaj" ima jedan parametar - ulaznu listu koja sadrži neki broj cifara. Ova funkcija treba da pokrene jednu novu nit u kojoj će pozivom funkcije "obrniRedosled" da izvrši obrtanje redosleda elemenata ulazne liste i da novodobijenu listu vrati kao svoju povratnu vrednost.

Test korektnosti funkcije "izracunaj" je dat u fajlu main.cpp, u funkciji "testirajIzracunaj".
*/

#include <iostream>

#include "obrtanje.hpp"
#include "niti.hpp"

using namespace std;

void testirajObrniRedosled() {
    list<int> ulaz = {1, 2, 3, 5, 4};
    list<int> rezultat;

    obrniRedosled(ulaz, rezultat);

    cout << "Rezultat izvrsavanja funkcije obrniRedosled():" << endl;

    for (list<int>::const_iterator it = rezultat.begin(); it != rezultat.end(); it++)
        cout << *it << " ";
    cout << endl;
}

void testirajIzracunaj() {
    list<int> ulaz = {1, 2, 3, 5, 4};

    list<int> rezultat = izracunaj(ulaz);

    cout << "Rezultat izvrsavanja funkcije izracunaj():" << endl;

    for (list<int>::const_iterator it = rezultat.begin(); it != rezultat.end(); it++)
        cout << *it << " ";
    cout << endl;
}

int main() {
    testirajObrniRedosled();
    testirajIzracunaj();

    return 0;
}
