/*
Napraviti konkurentni program koji stvara zadati broj niti a potom u svakoj niti ispisuje redni broj te niti. Korisnik prilikom pokretanja programa zadaje željeni broj niti. Prilikom instanciranja niti njoj se prosleđuje njen redni broj koji ona potom ispisuje.

Potrebno je implementirati dve funkcije:
1) funkciju "ispisi" koja se nalazi u fajlu ispis.h
2) funkciju "izracunaj" koja se nalazi u fajlu niti.h

1)
Ulaz u funkciju "ispisi" je jedan int broj koji predstavlja redni broj koji funkcija treba da ispiše.

Test korektnosti funkcije "ispisi" je dat u fajlu main.cpp, u funkciji "testirajIspisi".

2)
Funkcija "izracunaj" ima jedan parametar - broj niti koje treba kreirati. Ova funkcija treba da pokrene onoliko niti koliko je navedeno u parametru a kao funkciju tih niti treba da iskoristi funkciju koja je implementirana u prvom delu zadatka (funkciju "ispisi").

Test korektnosti funkcije "izracunaj" je dat u fajlu main.cpp, u funkciji "testirajIzracunaj".
*/

#include <iostream>
#include <list>

#include "ispis.hpp"
#include "niti.hpp"

using namespace std;

void testirajIspisi() {
    cout << "Rezultat izvrsavanja funkcije ispisi():" << endl;

    ispisi(33);
}

void testirajIzracunaj() {
    cout << "Unesite broj niti koje je potrebno kreirati:" << endl;
    int brojNiti;
    cin >> brojNiti;

    cout << "Rezultat izvrsavanja funkcije izracunaj():" << endl;
    izracunaj(brojNiti);
}

int main() {
    testirajIspisi();
    testirajIzracunaj();

    return 0;
}
