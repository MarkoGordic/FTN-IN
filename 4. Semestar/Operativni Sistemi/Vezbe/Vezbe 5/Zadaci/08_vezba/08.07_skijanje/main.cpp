/**
 * Napisati C++ program koji iz ulazne datoteke cita podatke o temperaturi u toku vikenda sa ski 
 * staza na Kopaoniku, Zlatiboru i Jahorini i odredjuje koji dani i na kojoj planini su idealni 
 * za skijanje a koji nisu. Neki idealni opseg temperature za skijanje je od -5 do 3 stepena.
 * 
 * Za svaku od planina postoji posebna datoteka cije ime se sastoji od imena planine i prosirenja
 * (ekstenzije) ".txt". U svakoj pojedinacnoj datoteci se u jednom redu nalaze podaci za jedan dan. 
 * Jedan red sadrzi redom ime_dana, datum, i potom izmerene temperature. Temperatura se meri na 
 * svakih sat vremena, pocevsi od 8 ujutru, do 8 uvece. Svi podaci su odvojeni razmakom.
 * 
 * Izgled jednog reda iz ulaznih datoteka "Kopaonik.txt" "Zlatibor.txt" "Jahorina.txt"
 * 
 *     subota 01.02.  -15 -13 -10 -8 -3 0 -2 -3 2 2 -5 -7 -3
 * 
 * NAPOMENA: ukoliko ne postoji neka od ulaznih datoteka, treba samo napisati poruku da datoteka
 * ne postoji i nastaviti dalje sa izvrsavanjem programa uz oslonac na podatke iz preostalih
 * datoteka
 * 
 * Treba za svaki dan pronaci najnizu i najvisu dnevnu temperaturu. Ukoliko minimalna i maksimalna
 * temperatura upadaju u navedeni opseg, treba informacije za taj dan ispisati u datoteku 
 * "idealno.txt", u suprotnom u datoteku "lose.txt".
 *
 * Ispis u izlaznu datoteku treba da prati format:
 *     <ime_planine> [<ime_dana> <datum>] <min. temp.> >> <maks. temp.>
 * 
 * Primer ispisa u bilo kojoj od izlaznih datoteka "idealno.txt", "lose.txt":
 * 
 *     Kopaonik [subota 01.02.] -15 >> 2
 *
 * Treba napraviti jednu nit koja ce samo citati podatke iz ulaznih datoteka, jednu nit koja ce 
 * samo pisati spremljene podatke u izlazne datoteke i 4 niti radnika koji ce na osnovu podataka iz
 * ulaznih datoteka generisati sve neophodno za ispis u izlazne datoteke.
*/

#define BR_RADNIKA 4
#define BR_MERENJA_TEMPERATURE 13
#define MINIMALNA_IDEALNA_TEMPERATURA -5
#define MAKSIMALNA_IDEALNA_TEMPERATURA 3

using namespace std;

class StanjeSkijalistaNaDan {
private:
    // TODO dodati polja po potrebi
public:
    // TODO dodati metode po potrebi
private:
    // TODO dodati metode po potrebi
};

/** Klasa koja modeluje "postansko sanduce" izmedju citaca i radnika.
*/
template<typename T>
class RedoviIzDatoteke {
private:
    mutex podaci_mx;                       // propusnica za sinhronizaciju nad svim poljima klase
    // TODO dodati polja po potrebi
public:
    RedoviIzDatoteke(): kraj(false) {}

    void dodaj(T redIzDatoteke) {
        // TODO
    }

    bool preuzmi(T &redIzDatoteke) {
        // TODO
    }

    // TODO dodati metode po potrebi

private:
    /**
     * Provera da li treba da cekamo podatke. Vraca istinu samo onda kada u kolekciji
     * nema podataka ali istovremeno i nije objavljen kraj stvaranja podataka.
    */
    bool daLiCekamPodatke() {
        // TODO
    }

    /**
     * Provera da li smo zavrsili sa citanjem podataka. Vraca istinu samo onda kada nema vise podataka
     * u kolekciji i sve niti stvaraoci podataka su se odjavili.
    */
    bool jeLiKraj() {
        // TODO
    }
};


/** Klasa koja modeluje "postansko sanduce" izmedju radnika i pisaca.
*/
template<typename T>
class PodaciZaIspis {
private:
    mutex podaci_mx;                       // propusnica za sinhronizaciju nad svim poljima klase
    // TODO dodati polja po potrebi
public:
    PodaciZaIspis(): kraj(false), br_stvaralaca_podataka(0) {}  // na pocetku nije kraj i nema radnika

    void dodaj(T stanjeSkijalista) {
        // TODO
    }

    bool preuzmi(T &stanjeSkijalista) {
        // TODO
    }

    // TODO dodati metode po potrebi

private:
    /**
     * Provera da li treba da cekamo podatke. Vraca istinu samo onda kada u kolekciji
     * nema podataka ali istovremeno i nije objavljen kraj stvaranja podataka.
    */
    bool daLiCekamPodatke() {
        // TODO
    }

    /**
     * Provera da li smo zavrsili sa citanjem podataka. Vraca istinu samo onda kada nema vise podataka
     * u kolekciji i sve niti stvaraoci podataka su se odjavili.
    */
    bool jeLiKraj() {
        // TODO
    }
};

void citac(vector<string> imena_ulaznih_datoteka, RedoviIzDatoteke<string>& redovi_iz_ulaznih_datoteka) {
    // TODO
}

void radnik(RedoviIzDatoteke<string>& redovi_iz_ulaznih_datoteka, PodaciZaIspis<StanjeSkijalistaNaDan>& pripremljeni_podaci){
    // TODO
}

void pisac(PodaciZaIspis<StanjeSkijalistaNaDan>& pripremljeni_podaci) {
    // TODO
}


int main() {
    RedoviIzDatoteke<string> redovi_iz_ulaznih_datoteka;
    PodaciZaIspis<StanjeSkijalistaNaDan> pripremljeni_podaci;
    vector<string> imena_ulaznih_datoteka = {"Kopaonik.txt", "Zlatibor.txt", "Jahorina.txt"};

    thread th_reader(citac, imena_ulaznih_datoteka, ref(redovi_iz_ulaznih_datoteka));
    thread th_writer(pisac, ref(pripremljeni_podaci));
    thread th_workers[BR_RADNIKA];

    for(auto &th: th_workers){
        th = thread(radnik, ref(redovi_iz_ulaznih_datoteka), ref(pripremljeni_podaci));
    }

    th_reader.join();
    for(auto &th: th_workers) {
        th.join();
    }
    th_writer.join();
    
    return 0;
}