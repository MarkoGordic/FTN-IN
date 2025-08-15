/*
Napraviti konkurentni program koji pravi srpsko-engleski rečnik iz zadatog englesko-srpskog rečnika. Posao pravljenja rečnika treba obaviti u posebnoj niti.

Napomena: redosled reči u rečnicima (i ulaznom i u onom koji je dobijen kao rezultat pravljenja rečnika) ne mora biti u redosledu u kojem se reči pojavljuju u programu (usled osobine asocijativnih kolekcija da one interno menjaju raspored svojih elemenata).

Potrebno je implementirati dve funkcije:
1) funkciju "napraviRecnik" koja se nalazi u fajlu recnik.h
2) funkciju "izracunaj" koja se nalazi u fajlu niti.h

1)
Ulaz u funkciju "napraviRecnik" je par mapa. Prva mapa je englesko-srpski rečnik (polazni rečnik) a druga mapa je ona koju treba popuniti, tako da ona bude srpsko-engleski rečnik.

Test korektnosti funkcije "napraviRecnik" je dat u fajlu main.cpp, u funkciji "testirajNapraviRecnik".

2)
Funkcija "izracunaj" ima jedan parametar - ulazni rečnik (mapu reči kod koje je ključ reč na engleskom a podatak prevod te reči na srpski). Ova funkcija treba da pokrene novu nit a kao funkciju te niti treba da iskoristi funkciju koja je implementirana u prvom delu zadatka (funkciju "napraviRecnik").
Njena povratna vrednost treba da bude napravljeni srpsko-engleski rečnik.

Test korektnosti funkcije "izracunaj" je dat u fajlu main.cpp, u funkciji "testirajIzracunaj".
*/

#include <iostream>

#include "recnik.hpp"
#include "niti.hpp"

using namespace std;

void testirajNapraviRecnik() {
    map<string, string> engSrp = {{"one",   "jedan"},
                                  {"two",   "dva"},
                                  {"three", "tri"},
                                  {"four",  "cetiri"},
                                  {"five",  "pet"},
                                  {"six",   "sest"},
                                  {"seven", "sedam"},
                                  {"eight", "osam"},
                                  {"nine",  "devet"},
                                  {"ten",   "deset"}};

	cout << "ENGLESKO-SRPSKI:" << endl;
	for (map<string, string>::const_iterator it = engSrp.begin(); it != engSrp.end(); it++) {   // Ispis engelsko-srpskog rečnika
		cout << it->first << " : " << it->second << endl;
	}

    map<string, string> srpEng;
    napraviRecnik(engSrp, srpEng);

    cout << "Rezultat izvrsavanja funkcije napraviRecnik(): " << endl;

	cout << "SRPSKO-ENGLESKI:" << endl;
	for (map<string, string>::const_iterator it = srpEng.begin(); it != srpEng.end(); it++) {   // Ispis srpsko-engelskog rečnika.
		cout << it->first << " : " << it->second << endl;
	}
}

void testirajIzracunaj() {
    map<string, string> engSrp = {{"one",   "jedan"},
                                  {"two",   "dva"},
                                  {"three", "tri"},
                                  {"four",  "cetiri"},
                                  {"five",  "pet"},
                                  {"six",   "sest"},
                                  {"seven", "sedam"},
                                  {"eight", "osam"},
                                  {"nine",  "devet"},
                                  {"ten",   "deset"}};

	cout << "ENGLESKO-SRPSKI:" << endl;
	for (map<string, string>::const_iterator it = engSrp.begin(); it != engSrp.end(); it++) {   // Ispis engelsko-srpskog rečnika
		cout << it->first << " : " << it->second << endl;
	}

    map<string, string> srpEng = izracunaj(engSrp);

    cout << "Rezultat izvrsavanja funkcije izracunaj(): " << endl;

	cout << "SRPSKO-ENGLESKI:" << endl;
	for (map<string, string>::const_iterator it = srpEng.begin(); it != srpEng.end(); it++) {   // Ispis srpsko-engelskog rečnika.
		cout << it->first << " : " << it->second << endl;
	}
}

int main() {
    testirajNapraviRecnik();
    testirajIzracunaj();

    return 0;
}
