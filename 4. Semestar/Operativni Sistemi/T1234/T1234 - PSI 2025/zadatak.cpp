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
#include <queue>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <mutex>
#include <condition_variable>
#include <algorithm>
#include <thread>

using namespace std;

#define BROJ_RADNIKA 3

struct izlazni_podaci {
    vector<double> ulazi;
    vector<double> obradjeni;
    unsigned id;
    unsigned char komanda;
    bool za_kantu = false;
};

/** Klasa koja modeluje "postansko sanduce" izmedju citaca i radnika.
*/
template<typename T>
class UlazniPodaci {
private:
    queue<T> ulazni_podaci;
    mutex mtx;
    condition_variable cv;
    bool kraj = false; 
public:
    UlazniPodaci() {}

    void dodaj(T neobradjeni_podaci) {
        {
            unique_lock<mutex> lk(mtx);
            ulazni_podaci.push(neobradjeni_podaci);
        }

        cv.notify_one();
    }

    bool preuzmi(T &neobradjeni_podaci) {
        {
            unique_lock<mutex> lk(mtx);
            
            while(!kraj && ulazni_podaci.empty())
                cv.wait(lk);
            
            if(ulazni_podaci.empty()) return false;

            neobradjeni_podaci = ulazni_podaci.front();
            ulazni_podaci.pop();
            return true;
        }
    }

    void zavrsi(){
        {
            unique_lock<mutex> lk(mtx);
            kraj = true;
        }

        cv.notify_all();
    }
};


/** Klasa koja modeluje "postansko sanduce" izmedju radnika i pisaca.
*/
template<typename T>
class IzlazniPodaci {
private:
    queue<T> izlazni_podaci;
    mutex mtx;
    condition_variable cv;
    bool kraj = false; 
public:
    IzlazniPodaci() {}

    void dodaj(T obradjeni_podaci) {
        {
            unique_lock<mutex> lk(mtx);
            izlazni_podaci.push(obradjeni_podaci);
        }

        cv.notify_one();
    }

    bool preuzmi(T &obradjeni_podaci) {
        {
            unique_lock<mutex> lk(mtx);
            
            while(!kraj && izlazni_podaci.empty())
                cv.wait(lk);
            
            if(izlazni_podaci.empty()) return false;

            obradjeni_podaci = izlazni_podaci.front();
            izlazni_podaci.pop();
            return true;
        }
    }

    void zavrsi(){
        {
            unique_lock<mutex> lk(mtx);
            kraj = true;
        }
        
        cv.notify_all();
    }
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
    string trenutni;
    unsigned trenutni_id;
    unsigned char trenutna_komanda;
    vector<double> ulazni_brojevi;

    double suma_brojeva = 0;
    int ima_vecih = 0;
    double zbir = 0;
    double prosek = 0;
    bool prosli_prvi = false;
    double trenutno = 0;
    
    while(ulaz.preuzmi(trenutni)){
        izlazni_podaci trenutni_izlaz;
        vector<double> obradjeni_brojevi;
        ulazni_brojevi = izdvoj_brojeve(trenutni, trenutni_id, trenutna_komanda);

        trenutni_izlaz.id = trenutni_id;
        trenutni_izlaz.komanda = trenutna_komanda;
        trenutni_izlaz.ulazi = ulazni_brojevi;
        trenutni_izlaz.za_kantu = false;

        switch(trenutna_komanda) {
            case 1:
                suma_brojeva = 0;
                ima_vecih = 0;

                // racunamo prosek
                for(double x : ulazni_brojevi)
                    suma_brojeva += x;
                
                if(!ulazni_brojevi.empty()) {
                    prosek = suma_brojeva / ulazni_brojevi.size();
                    for(double x : ulazni_brojevi) if(x > prosek) ima_vecih++;

                    obradjeni_brojevi.push_back(prosek);
                    obradjeni_brojevi.push_back(ima_vecih);
                }

                break;
            case 2:
                if(!ulazni_brojevi.empty()) {
                    sort(ulazni_brojevi.begin(), ulazni_brojevi.end(), greater<double>());
                    zbir = ulazni_brojevi.front() + ulazni_brojevi.back();
                    obradjeni_brojevi.push_back(zbir);
                }

                break;
            case 3:
                prosli_prvi = false;

                for(double x : ulazni_brojevi) {
                    if(!prosli_prvi){
                        trenutno = x;
                        obradjeni_brojevi.push_back(x);
                        prosli_prvi = true;
                    } else {
                        trenutno *= x;
                        obradjeni_brojevi.push_back(trenutno);
                    }
                }

                break;
            default:
                trenutni_izlaz.za_kantu = true;
                break;
        }

        if(!trenutni_izlaz.za_kantu) {
            trenutni_izlaz.obradjeni = std::move(obradjeni_brojevi);
        }
        
        // saljemo rezultat stampacu
        izlaz.dodaj(trenutni_izlaz);
    }
}

/**
 * Logika citaca - nit koja radi citanje iz ulazne datoteke i salje u ulaznu
 * kolekciju za radnike
*/
void citac_nit(UlazniPodaci<string> &ulaz) {
    ifstream fulaz("ulaz.txt");

    if(!fulaz){
        cerr << "Doslo je do opasnog ukenjavanja koda. Nismo otvorili fajl, a kod je napunio gace u mejduvremenu." << endl;
        ulaz.zavrsi();
        return;
    }

    string trenutna;
    while(getline(fulaz, trenutna)) {
        if(!trenutna.empty()) {
            ulaz.dodaj(trenutna);
        }
    }

    ulaz.zavrsi();
}

/**
 * Logika stampaca - nit koja radi pisanje u izlaznu datoteku podataka dobijenih
 * od radnika
*/
void stampac_nit(IzlazniPodaci<struct izlazni_podaci> &izlaz) {
    ofstream fparni("vece10.txt");
    ofstream fneparni("manje10.txt");
    ofstream fkanta("kanta.txt");

    if(!fparni || !fneparni || !fkanta){
        cerr << "Nesto od ponudjenog se ukenjalo, zao nam je :(. Nismo uspeli da otvorimo jedan od 3 izlazna fajla";
        return;
    }

    izlazni_podaci trenutni;
    while(izlaz.preuzmi(trenutni)) {
        if(trenutni.za_kantu) {
            fkanta << trenutni.id << ":" << (unsigned)trenutni.komanda;
            for(double x : trenutni.ulazi)
                fkanta << ":" << x;
            
            fkanta << "\n";
            continue;
        }
        
        if(trenutni.obradjeni.size() > 10) {
            fparni << trenutni.id;
            for(double x : trenutni.obradjeni)
                fparni << ":" << x;

            fparni << "\n";
            continue;
        } else {
            fneparni << trenutni.id;
            for(double x : trenutni.obradjeni)
                fneparni << ":" << x;

            fneparni << "\n";
            continue;
        }
    }
}

int main() {
    UlazniPodaci<string> ulaz;
    IzlazniPodaci<izlazni_podaci> izlaz;

    thread citac(citac_nit, ref(ulaz));
    thread stampac(stampac_nit, ref(izlaz));
    thread radnici[BROJ_RADNIKA];
    for(int i = 0; i < BROJ_RADNIKA; i++)
        radnici[i] = thread(radnik_nit, ref(ulaz), ref(izlaz));

    citac.join();
    for(int i = 0; i < BROJ_RADNIKA; i++)
        radnici[i].join();
    izlaz.zavrsi();
    stampac.join();

    exit(0);
}