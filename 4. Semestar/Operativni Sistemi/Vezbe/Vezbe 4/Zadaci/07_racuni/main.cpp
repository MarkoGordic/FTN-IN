/*
Napraviti program koji simulira prenos novca unutar jedne banke, sa jednog bankovnog računa na drugi. Iznosi na računima u banci su predstavljeni datim nizom racuni. Taj niz sadrži onoliko elemenata koliko iznosi konstanta UKUPNO_RACUNA. Svaki element niza predstavlja jedan račun u banci.

Funkcija main() popunjava sve račune u banci iznosom POCETNI_IZNOS. Potom ona kreira dve niti koje vrše transfer novca sa jednog računa na drugi. Ovaj prenos obavlja funkcija transfer().

Data funkcija transfer() predstavlja telo niti koje vrše prenos novca. Funkcija 10 puta na slučajan način bira dva računa i neki iznos novca i poziva funkciju prebaci() koja skida novac sa prvog racuna i dodaje ga na drugi račun. Ovu funkciju je potrebno implementirati.
*/

#include <iostream>
#include <thread>
#include <mutex>

#define UKUPNO_RACUNA 3
#define POCETNI_IZNOS 50

using namespace std;

struct retVal{
    double staro; // Iznos novca na računu pre prenosa
    double novo; // Iznos novca na računu posle prenosa
};

double racuni[UKUPNO_RACUNA]; // Svaki element niza predstavlja iznos novca na odgovarajućem računu

// izvor - indeks računa SA KOJEG se prebacuje novac (indeks u nizu "racuni")
// cilj - indeks računa NA KOJI se prebacuje novac (indeks u nizu "racuni")
// iznos - novčani iznos koji se prebacuje
// Nakon skidanja novca sa prvog računa potrebna je jedna sekunda da se novac uplati na drugi račun (trajanje ove operacije simulirati pauziranjem niti).
// Povratna vrednost funkcije je struktura retVal koja sadrži iznos na prvom računu (izvor) pre i posle transakcije.
retVal prebaci(int izvor, int cilj, double iznos) {
	// Implementirati...
}


void transfer() {
	// Vrši se deset transakcija:
    for (int i = 0; i < 10; i++) {
        int izvor = rand()%UKUPNO_RACUNA; // Slučajni odabir prvog računa
        int cilj = (izvor+5)%UKUPNO_RACUNA; // Slučajni odabir drugog računa
        int iznos = rand()%10 + 1; // Slučajni odabir iznosa
        retVal r = prebaci(izvor, cilj, iznos); // Prebacivanje novca sa jednog računa na drugi
        // Razlika između novog i starog iznosa na računu mora biti jednaka iznosu koji se prebacivao.

		if ((r.staro - r.novo) == iznos)
            cout << "Uspesno: ";
		else
            cout << "NEUSPESNO: ";

        cout << "Prebaceno " << iznos << " sa racuna " << izvor << " na racun " << cilj << ". Na izvoru bilo " << r.staro << ", a ostalo " << r.novo << endl;
    }
}

// Funkcija za računanje ukupnog iznosa na svim računima`u banci:
double ukupno_u_banci() {
    double ukupno = 0;
    for (int i = 0; i < UKUPNO_RACUNA; i++)  {
        ukupno += racuni[i];
    }
    return ukupno;
}

int main() {
	// Inicijalizujemo iznos na svakom računu:
    for (int i = 0; i < UKUPNO_RACUNA; i++)  {
        racuni[i] = POCETNI_IZNOS;
    }
    cout << "Ukupno novca u banci, na pocetku: " << ukupno_u_banci() << endl;

    // Napravimo 2 niti koje će vršiti transfere sa računa na račun:
	thread t1(transfer);
    thread t2(transfer);

    t1.join();
    t2.join();

    cout << "Ukupno novca u banci, na kraju: " << ukupno_u_banci() << endl;

    return 0;
}
