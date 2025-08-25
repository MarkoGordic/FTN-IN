// INDEKS IME PREZIME

#include <iostream>
#include <string>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <fstream>
#include <thread>
#include <algorithm>
#include <vector>

using namespace std;

#define BROJ_RADNIKA 4
#define ULAZNA_DATOTEKA "mila.me"
#define IZLAZ_DATOTEKA_PLEJLISTA "plejlista_parni.txt"
#define IZLAZ_DATOTEKA_PORUKA "poruka.txt"

struct Pesma {
    string ime_pesme;
    string ime_autora;
    int duzina;
    int kljuc;
    int id_kljuca;
    string ime_albuma;
    int id;
};

struct DeoPoruke {
    char karakter;
    int id_kljuca;
};

template<typename T>
class UlazniPodaci {
private:
    // TODO
public:
    UlazniPodaci() {
        // TODO
    }

    void dodaj(T neobradjeni_podaci) {
        // TODO
    }

    bool preuzmi(T &neobradjeni_podaci) {
        // TODO
    }

    void zavrsi() {
        // TODO
    }
};

template<typename T>
class IzlazniPodaciPlejlista {
private:
    // TODO
public:
    IzlazniPodaciPlejlista() {
        // TODO
    }

    void dodaj(T obradjeni_podaci) {
        // TODO
    }

    bool preuzmi(T &obradjeni_podaci) {
        // TODO
    }

    void zavrsi() {
        // TODO
    }
};

class IzlazniPodaciPoruka {
private:
    // TODO
public:
    IzlazniPodaciPoruka() {
        // TODO
    }

    void dodaj(DeoPoruke obradjeni_podaci) {
        // TODO
    }

    bool preuzmi(DeoPoruke &obradjeni_podaci) {
        // TODO
    }

    void zavrsi() {
        // TODO
    }
};

Pesma obradi_pesmu(string neobradjeni_podaci) {
    Pesma pesma;
    int pozicija = 0;
    int prethodna_pozicija = 0;
    int broj_polja = 0;

    while((pozicija = neobradjeni_podaci.find('#', prethodna_pozicija)) != string::npos) {
        string polje = neobradjeni_podaci.substr(prethodna_pozicija, pozicija - prethodna_pozicija);

        switch(broj_polja) {
            case 0: pesma.ime_pesme = polje; break;
            case 1: pesma.ime_autora = polje; break;
            case 2: pesma.duzina = stoi(polje); break;
            case 3: pesma.kljuc = stoi(polje); break;
            case 4: pesma.id_kljuca = stoi(polje); break;
            case 5: pesma.ime_albuma = polje; break;
        }

        prethodna_pozicija = pozicija + 1;
        broj_polja++;
    }

    if(prethodna_pozicija < (int)neobradjeni_podaci.length()) {
        string polje = neobradjeni_podaci.substr(prethodna_pozicija);
        pesma.id = stoi(polje);
    }

   return pesma;
}

void radnik_nit(UlazniPodaci<string> &ulaz, IzlazniPodaciPlejlista<Pesma> &izlaz_plejlista, IzlazniPodaciPoruka &izlaz_poruka) {
    // TODO
}

void citac_nit(UlazniPodaci<string> &ulaz) {
    // TODO
}

void stampac_plejliste_nit(IzlazniPodaciPlejlista<Pesma> &izlaz_plejlista) {
    // TODO
}

void stampac_poruke_nit(IzlazniPodaciPoruka &izlaz_poruka) {
    // TODO
}

int main() {
    // TODO
    return 0;
}
