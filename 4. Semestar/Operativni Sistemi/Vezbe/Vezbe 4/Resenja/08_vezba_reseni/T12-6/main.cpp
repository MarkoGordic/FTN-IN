/*
Napraviti konkurentni program koji traži reč suprotnog značenja (antonim) od zadate reči. Konkurentnost rešenja se ogleda u tome što se pronalaženje reči treba obaviti u posebnoj niti.

Zadat je rečnik (mapa) u kojem se navode parovi reč - suprotna reč. Iako je u ovoj mapi jedna od reči ključ a druga podatak mape, reči su ravnopravne - odnosno, kada se traži reč suprotnog značenja, moraju se pretražiti i kjučevi i sve vrednosti u mapi.

Potrebno je implementirati dve funkcije:
1) funkciju "nadjiAntonim" koja se nalazi u fajlu antonim.h
2) funkciju "izracunaj" koja se nalazi u fajlu niti.h

1)
Ulaz u funkciju "nadjiAntonim" je mapa koja sadrži parove reč - suprotna reč. Ovoj funkciji se takođe prosleđuje reč kojoj se traži antonim, kao i parametar koji treba popuniti, tako da nakon izvršenja funkcije u njemu stoji pronađeni antonim.

Test korektnosti funkcije "nadjiAntonim" je dat u fajlu main.cpp, u funkciji "testirajNadjiAntonim".

2)
Funkcija "izracunaj" ima jedan parametar - ulazni rečnik i reč kojoj se traži antonim. Ova funkcija treba da pokrene novu nit a kao funkciju te niti treba da iskoristi funkciju koja je implementirana u prvom delu zadatka (funkciju "nadjiAntonim").
Njena povratna vrednost treba da bude pronađena reč suprotnog značenja.

Test korektnosti funkcije "izracunaj" je dat u fajlu main.cpp, u funkciji "testirajIzracunaj".
*/

#include <iostream>

#include "antonim.hpp"
#include "niti.hpp"

using namespace std;

void testirajNadjiAntonim() {
    map<string, string> recnik = {{"dobro",   "lose"},
                                  {"tamno",   "svetlo"},
                                  {"veliko",  "malo"},
                                  {"dugacko", "kratko"},
                                  {"tesko",   "lako"}};

    string rezultat;
    nadjiAntonim(recnik, "lako", rezultat);

    cout << "Rezultat izvrsavanja funkcije nadjiAntonim(): " << rezultat << endl;
}

void testirajIzracunaj() {
    map<string, string> recnik = {{"dobro",   "lose"},
                                  {"tamno",   "svetlo"},
                                  {"veliko",  "malo"},
                                  {"dugacko", "kratko"},
                                  {"tesko",   "lako"}};

    string rezultat = izracunaj(recnik, "veliko");

    cout << "Rezultat izvrsavanja funkcije izracunaj(): " << rezultat << endl;
}

int main() {
    testirajNadjiAntonim();
    testirajIzracunaj();

    return 0;
}
