/*
    Napraviti program koji ispituje ispravnost jednog od Marfijevih zakona, koji glasi:
    "Vas red je uvek najsporiji.".

    Simulirati placanje robe na tri kase. Rad svake kase predstavljen je jednom niti.
    Svaka nit dobija parametar koji predstavlja broj kupaca koje kasa treba da opsluzi.
    Broj kupaca je slucajan broj izmedju 1 i 30.
    Opsluzivanje svakog kupca simulirati uspavljivanjem niti na slucajan vremenski period izmedju 1 i 100 ms.

    Izracunati trajanje kupovine na svakoj od kasa.

    Na pocetku programa potrebno je pitati korisnika da unese redni broj kase na
    kojoj zeli da izvrsi kupovinu.
    Na kraju ispisati da li je Marfijev zakon potvrdjen.
    Ukoliko je kupovina na kasi koju je kupac izabrao trajala najduze, tada je Marfijev zakon potvrdjen.
*/

#include <iostream>
#include <thread>
#include <random>

using namespace std;
using namespace chrono;

const auto seme_pocetak = steady_clock::now();
const int UKUPNO_KASA = 3;
const int MAX_MILISEKUNDI_PO_KUPCU = 100;

default_random_engine gen;

void kasa(int broj_kupaca, duration<double, milli>& vreme_na_kasi) {
    uniform_int_distribution<int> trajanje_kupovine(1,100);
    system_clock::time_point pocetak = system_clock::now(); //evidentiramo pocetak rada kase
    for (int i = 0; i < broj_kupaca; i++) //simulacija kupovine. Svaki kupac provodi slucajan vremenski period na kasi
        this_thread::sleep_for(milliseconds(trajanje_kupovine(gen)));

    system_clock::time_point kraj = system_clock::now(); //evidentiranje zavrsetka rada kasa

    vreme_na_kasi= kraj - pocetak; //upisemo koliko je trajao rad kase
}

int main() {
    duration<double, nano> seme = steady_clock::now() - seme_pocetak;
    gen.seed(seme.count());// Inicijalizacija generatora slučajnih brojeva da pri svakom pokretanju daje različite brojeve

    uniform_int_distribution<int> br_klijenata(1,30);

    //odredjivanje kase na koju klijent zeli da ode
    int moja_kasa; 
    cout << "Unesite kasu na kojoj cete stati u red (0, 1 ili 2):" << endl;
    cin >> moja_kasa;

    //niz sadrzi vremena cekanja na svakoj od kasa
    duration<double, milli> vremena[UKUPNO_KASA];

    thread niti[UKUPNO_KASA];
    //kasi se prosledjuje koliko kupaca dolazi i promenljiva u koju treba da upise trajanje
    for (int i = 0; i < UKUPNO_KASA; ++i) {
        niti[i] = thread(kasa, br_klijenata(gen), ref(vremena[i]));
    }

    for (int i = 0; i < UKUPNO_KASA; ++i) {
        niti[i].join();
    }

    //nakon zavrsavanja rada niti, u nizu "vremena" su evidentirana trajanja kupovine na svakoj od kasa
    //sada medju tim vremenima treba naci najduze 
    duration<double, milli> max_trajanje = vremena[0];
    for (int i = 0; i < UKUPNO_KASA; i++) {
        cout << "Ukupno trajanje placanja na kasi " << i << " je: "
            << vremena[i].count() << " milisekundi. " << endl;

        if (vremena[i] > max_trajanje) { 
            max_trajanje = vremena[i];
        }
    }
	
    //ukoliko je najduze trajala kupovina na kasi koju je kupac izabrao, onda je marfijev zakon potrvrdjen
    if (vremena[moja_kasa] == max_trajanje)
        cout << "Vas red je najsporiji. Marfijev zakon potvrdjen." << endl;
    else
        cout << "Marfijev zakon nije potvrdjen." << endl;
    
    return 0;
}
