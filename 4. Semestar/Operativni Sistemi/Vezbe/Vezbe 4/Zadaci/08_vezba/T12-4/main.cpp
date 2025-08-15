/*
Napraviti konkurentni program koji pronalazi element najbliži nuli iz zadatog vektora brojeva. Ovaj zadatak potrebno je izvršiti iz tri nove niti, tako da svaka nit pretražuje po trećinu ulaznog vektora. Dužina ulaznog vektora uvek će biti deljiva sa 3.

Potrebno je implementirati dve funkcije:
1) funkciju "pretrazi" koja se nalazi u fajlu pretraga.h
2) funkciju "izracunaj" koja se nalazi u fajlu niti.h

1)
Ulaz u funkciju "pretrazi" je par iteratora kojima se zadaje opseg elemenata koje je potrebno pretražiti. Postoji još jedan parametar ove funkcije i on služi da se vrati rezultat (treba da bude postavljen na vrednost pronađenog elementa koji je najbliži nuli).

Test korektnosti funkcije "pretrazi" je dat u fajlu main.cpp, u funkciji "testirajPretrazi".

2)
Funkcija "izracunaj" ima jedan parametar - ulazni vektor razlomljenih brojeva (double brojeva). Ova funkcija treba da pokrene tri niti a kao funkciju tih niti treba da iskoristi funkciju koja je implementirana u prvom delu zadatka (funkciju "pretrazi").

Test korektnosti funkcije "izracunaj" je dat u fajlu main.cpp, u funkciji "testirajIzracunaj".
*/

#include <iostream>

#include "pretraga.hpp"
#include "niti.hpp"

using namespace std;

void testirajPretrazi() {
    vector<double> ulaz = {  5,
                            -1.5,
                            -3,
                             2.1,
                             3};
    double rezultat;

    pretrazi(ulaz.begin(), ulaz.end(), rezultat);
    cout << "Rezultat izvrsavanja funkcije pretrazi(): " << rezultat << endl;
}

void testirajIzracunaj() {
    vector<double> ulaz = {  5,
                            -1.5,
                            -3,
                             2.1,
                             3,
                             0.27,
                            17,
                            -1.75,
                             0.33};

    double rezultat = izracunaj(ulaz);
    cout << "Rezultat izvrsavanja funkcije izracunaj(): " << rezultat << endl;
}

int main() {
    testirajPretrazi();
    // Otkomentarisati kada implementirate funkciju "izracunaj":
    //testirajIzracunaj();

    return 0;
}
