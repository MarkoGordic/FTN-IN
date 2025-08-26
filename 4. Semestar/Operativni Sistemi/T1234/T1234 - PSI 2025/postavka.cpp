// INDEKS IME PREZIME
/**
 * Napisati konkurentni C++ program koji iz ulazne datoteke "ulaz.txt" cita red po red, obradjuje ih po navedenim komandama i potom rezultat smesta u izlazne datoteke "neparni.txt" i "parni.txt".
 *
 * U svakoj ulaznoj datoteci su podaci podeljeni delimiterom ':', i prate
 * sledeci format:
 *     1. broj: ID, unsigned int
 *     2. broj: komanda, unsigned char, odreduje sta treba raditi sa brojevima
 *                koji slede, pritom obratiti paznju da je komanda takodje BROJ
 *     3+. brojevi: brojevi, double, koje treba obraditi po definiciji komande
 *
 * Ulazna datoteka je "ulaz.txt".
 *
 * Komande koje postoje su:
 *     1) Izracunaj prosek niza, izracunaj koliko je elemenata niza vecih od proseka, ispisati oba
 *     2) Sortiraj niz u opadajucem redosledu i saberi prvi i poslednji element niza, vratiti zbir
 *     3) (primer: za niz {1, 2, 3, 4} novi niz je {1 2 6 24}) Napraviti novi niz ciji su elementi proizvod svih prethodnih elemenata niza (prvi element ostaje isti)
 * 
 * U svakoj izlaznoj datoteci su podaci nakon transformacije upisani u jedan
 * red, podeljeni delimiterom ':', i prate sledeci format:
 *     1. broj: ID, neoznacen ceo broj
 *     2+. brojevi: razlomljeni broj/evi dobijen/i transformacijom na osnovu
 *                    komande
 *
 * Izlazni podaci se rasporedjuju u izlazne datoteke i to:
 *     "vece10.txt" - rezultati se unose ako je broj brojeva veci od 10
 *     "manje10.txt" - rezultati se unose ako je broj brojeva manji ili jednak 10
 *
 * Treba napraviti jednu citac nit koja ce samo citati redove iz ulaznih
 * datoteka, jednu stampac nit koja ce samo pisati izlazne podatke u izlazne
 * datoteke i 3 niti radnika koji ce transformisati ulazne podatke u izlazne.
 * 
 * NAPOMENE:
 * Komanda 0 nikada nece postojati u ulaznim datotekama.
 * Redove sa nepostojecim komandama napisati u datoteku "kanta.txt" tako da budu
 * ispisani id, komanda i potom polazni brojevi podeljeni delimiterom ':'.
*/
#include <sstream>

#define BROJ_RADNIKA 3

struct izlazni_podaci {
    // TODO
};

/** Klasa koja modeluje "postansko sanduce" izmedju citaca i radnika.
*/
template<typename T>
class UlazniPodaci {
private:
    // TODO dodati polja ako je potrebno
public:
    UlazniPodaci() {}

    void dodaj(T neobradjeni_podaci) {
        // TODO
    }

    bool preuzmi(T &neobradjeni_podaci) {
        // TODO
    }

    // TODO dodati jos neku metodu ako je potrebno
};


/** Klasa koja modeluje "postansko sanduce" izmedju radnika i pisaca.
*/
template<typename T>
class IzlazniPodaci {
private:
    // TODO dodati polja ako je potrebno
public:
    IzlazniPodaci() {}

    void dodaj(T obradjeni_podaci) {
        // TODO
    }

    bool preuzmi(T &obradjeni_podaci) {
        // TODO 
    }

    // TODO dodati jos neku metodu ako je potrebno
};


/**
 * Parsiranje reda iz ulazne datoteke
 *   parametri:
 *     - red_datoteke, sadrzaj jednog reda ulazne datoteke
 *     - id, adresa gde ce biti upisan id procitan iz reda
 *     - komanda, adresa gde ce biti upisan id komande procitan iz reda
 *   vraca: kolekciju brojeva koje radnik treba da transformise po komandi
*/
vector<double> izdvoj_brojeve(const string red_datoteke, unsigned &id, unsigned char &komanda) {
    istringstream red_datoteke_tok(red_datoteke);
    vector<double> brojevi;
    string broj;

    if (getline(red_datoteke_tok, broj, ':'))
        id = stoul(broj);

    if (getline(red_datoteke_tok, broj, ':'))
        komanda = stoul(broj);

    while (getline(red_datoteke_tok, broj, ':'))
        brojevi.push_back(stod(broj));

    return brojevi;
}

/**
 * Logika radnika - niti koje vrse transformaciju ulaznih podataka u izlazne
 * podatke spremne za ispis.
*/
void radnik_nit(UlazniPodaci<string> &ulaz, IzlazniPodaci<struct izlazni_podaci> &izlaz) {
    // TODO
}

/**
 * Logika citaca - nit koja radi citanje iz ulazne datoteke i salje u ulaznu
 * kolekciju za radnike
*/
void citac_nit(UlazniPodaci<string> &ulaz) {
    // TODO
}

/**
 * Logika stampaca - nit koja radi pisanje u izlaznu datoteku podataka dobijenih
 * od radnika
*/
void stampac_nit(IzlazniPodaci<struct izlazni_podaci> &izlaz) {
    // TODO
}

int main() {
    // TODO

    exit(0);
}