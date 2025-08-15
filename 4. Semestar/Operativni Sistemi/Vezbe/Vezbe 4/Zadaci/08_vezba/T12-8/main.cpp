/*
Napraviti konkurentan program koji formira najbolju ponudu cena od dva zadata cenovnika (A i B). Cenovnici se zadaju uz pomoć map kontejnera, pri čemu ključ predstavlja naziv proizvoda (string) a podatak je cena proizvoda (double).

Program treba da podrazumeva da oba cenovnika (dve mape) sigurno sadrže iste proizvode (svaki proizvod se sigurno pojavljuje u obe). Samo se deo sa cenama razlikuje. Program treba da u novoj niti obavi ispitivanje - da pronađe nižu od dve cene i da je ubaci u rezultujući cenovnik. Nebitno je u kojoj radnji je nađen proizvod, rezultujući cenovnik (kao i dva ulazna) sadrži samo naziv proizvoda i cenu.

Primer:

Ulazni cenovnik A:
mleko = 85.50
sveska = 44.44
sampon = 140
kafa = 74.40

Ulazni cenovnik B:
mleko = 81.20
kafa = 79.90
sampon = 145.50
sveska = 40.33

Izlazni cenovnik treba da izgleda ovako:
kafa: 74.40
mleko: 81.20
sampon: 140
sveska: 40.33

Napomena: nebitno je kojim redosledom su prikazani proizvodi na izlazu (posledica korišćenja asocijativnih kontejnera u STL-u je da se gubi redosled elemenata).

Potrebno je implementirati dve funkcije:
1) funkciju "nadjiPovoljno" koja se nalazi u fajlu cenovnik.h
2) funkciju "izracunaj" koja se nalazi u fajlu niti.h

1)
Ulaz u funkciju "nadjiPovoljno" su mape koje sadrže dva ulazna cenovnika (A i B), kao i referenca na izlaznu mapu (koju funkcija treba da popuni sa povoljnim cenama, prema prethodno opisanom postupku).

Test korektnosti funkcije "nadjiPovoljno" je dat u fajlu main.cpp, u funkciji "testirajNadjiPovoljno".

2)
Funkcija "izracunaj" dobija dva parametra - dva ulazna cenovnika A i B. Ova funkcija treba da pokrene novu nit a za funkciju niti treba da se koristi funkcija "nadjiPovoljno" koja je realizovana u prvom delu zadatka.

Test korektnosti funkcije "izracunaj" je dat u main.cpp fajlu, u funkciji "testirajIzracunaj".

*/

#include <iostream>

#include "cenovnik.hpp"
#include "niti.hpp"

using namespace std;

void testirajNadjiPovoljno() {
    map<string, double> a = {{"mleko",   85.50},
                             {"kafa",    74.40},
                             {"sampon", 140.00},
                             {"sveska",  44.44}};
    map<string, double> b = {{"mleko",   81.20},
                             {"kafa",    79.90},
                             {"sampon", 145.50},
                             {"sveska",  40.33}};

    map<string, double> rezultat;
    nadjiPovoljno(a, b, rezultat);

    cout << "Rezultat izvrsavanja funkcije nadjiPovoljno():" << endl;

    for (map<string, double>::iterator it = rezultat.begin(); it != rezultat.end(); it++)
        cout << it->first << ": " << it->second << endl;
    cout << endl;
}

void testirajIzracunaj() {
    map<string, double> a = {{"mleko",   85.50},
                             {"kafa",    74.40},
                             {"sampon", 140.00},
                             {"sveska",  44.44}};
    map<string, double> b = {{"mleko",   81.20},
                             {"kafa",    79.90},
                             {"sampon", 145.50},
                             {"sveska",  40.33}};

    map<string, double> rezultat = izracunaj(a, b);

    cout << "Rezultat izvrsavanja funkcije izracunaj():" << endl;

    for (map<string, double>::iterator it = rezultat.begin(); it != rezultat.end(); it++)
        cout << it->first << ": " << it->second << endl;
    cout << endl;
}

int main() {
    testirajNadjiPovoljno();
    // Otkomentarisati kada implementirate funkciju "izracunaj":
    //testirajIzracunaj();

    return 0;
}
