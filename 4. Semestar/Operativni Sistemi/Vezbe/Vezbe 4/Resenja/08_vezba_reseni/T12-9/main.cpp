/*
Napraviti konkurentan program koji obračunava ukupnu cenu prilikom kupovine više proizvoda. Da bi se ovo izračunavanje moglo uraditi neophodno je da postoji cenovnik, koji predstavlja mapu u kojoj je ključ naziv proizvoda (string) a podatak je cena proizvoda (double). Pored cenovnika, ulaz predstavlja lista kupljenih proizvoda (obavezno STL lista) koja sadrži nazive proizvoda koji su kupljeni.
Obračunavanje ukupne cene vrši se tako što se prolazi kroz listu kupljenih proizvoda, za svaki se nalazi cena u cenovniku i taj iznos se dodaje na tekući zbir.

Jedan isti proizvod se može više puta pojavljivati u listi kupljenih proizvoda.

Primer:
Cenovnik:
mleko = 85.50
sampon = 140
kafa = 74.40

Lista kupljenih proizvoda:
{"mleko", "kafa", "mleko"}

Ukupan zbir: 245.40

Potrebno je implementirati dve funkcije:
1) funkciju "obracunajUkupno" koja se nalazi u fajlu obracun.h
2) funkciju "izracunaj" koja se nalazi u fajlu niti.h

1)
Ulaz u funkciju "obracunajUkupno" su lista kupljenih proizvoda i cenovnik, kao i referenca na broj koji funkcija treba da popuni ukupnom cenom svih kupljenih proizvoda.

Test korektnosti funkcije "obracunajUkupno" je dat u fajlu main.cpp, u funkciji "testirajObracunajUkupno".

2)
Funkcija "izracunaj" takođe kao parametre prima listu kupljenih proizvoda i cenovnik. Ova funkcija treba da pokrene novu nit a za funkciju niti treba da se koristi funkcija "obracunajUkupno" koja je realizovana u prvom delu zadatka.

Test korektnosti funkcije "izracunaj" je dat u main.cpp fajlu, u funkciji "testirajIzracunaj".

*/

#include <iostream>

#include "obracun.hpp"
#include "niti.hpp"

using namespace std;

void testirajObracunajUkupno() {
    map<string, double> cenovnik = {{"mleko", 85.50},
                                    {"sampon", 140},
                                    {"kafa", 74.40}};

    list<string> kupljeno = {"mleko", "mleko", "kafa"};

    double rezultat;
    obracunajUkupno(kupljeno, cenovnik, rezultat);

    cout << "Rezultat izvrsavanja funkcije obracunajUkupno(): " << rezultat << endl;
}

void testirajIzracunaj() {
    map<string, double> cenovnik = {{"mleko", 85.50},
                                    {"sampon", 140},
                                    {"kafa", 74.40}};

    list<string> kupljeno = {"mleko", "mleko", "kafa"};

    double rezultat = izracunaj(kupljeno, cenovnik);

    cout << "Rezultat izvrsavanja funkcije izracunaj(): " << rezultat << endl;
}

int main() {
    testirajObracunajUkupno();
    // Otkomentarisati kada implementirate funkciju "izracunaj":
    testirajIzracunaj();
}
