// IN 37/2023 Marko Gordic
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
 *     1) prebrojati parne brojeve na indeksima deljivim sa 3
 *     2) naci aritmeticku sredinu razlomljenih brojeva manjih od 16
 *     3) izracunati varijansu (sumu kvadrata odstupanja elemenata od srednje vrednosti deljeno sa brojem elemenata) razlomljenih brojeva
 *     4) napraviti novi niz koji sadrzi samo elemente koji su u originalnom nizu bili na indeksima sa cifrom 3 u zapisu
 *     5) elementi niza su xi vrednosti tacaka, koristiti formulu f(x) = sqrt(x) + 4 kako bi se odredile y vrednosti tacaka, napraviti novi niz koji sadrzi samo elemente koji su strogo iznad prave g(x) = 1/6*x + 3, ukoliko je y vrednost kompleksna ne dodavati je u rezultujuci niz
 * 
 * U svakoj izlaznoj datoteci su podaci nakon transformacije upisani u jedan
 * red, podeljeni delimiterom ':', i prate sledeci format:
 *     1. broj: ID, neoznacen ceo broj
 *     2+. brojevi: razlomljeni broj/evi dobijen/i transformacijom na osnovu
 *                    komande
 *
 * Izlazni podaci se rasporedjuju u izlazne datoteke i to:
 *     "neparni.txt" - rezultati za unose sa neparnim ID-om
 *     "parni.txt" - rezultati za unose sa parnim ID-om
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
#include <unistd.h>
#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <fstream>
#include <string>
#include <thread>
#include <cmath>
#include <vector>
using namespace std;

#define BROJ_RADNIKA 3

struct izlazni_podaci {
    unsigned id = 0;
    unsigned char komanda = 0;
    vector<double> ulazni;
    vector<double> obradjeni;
    bool validna_komanda = true;
};

/** Klasa koja modeluje "postansko sanduce" izmedju citaca i radnika.
*/
template<typename T>
class UlazniPodaci {
private:
    queue<T> podaci;
    mutex mtx;
    condition_variable cv;
    bool zavrsen_rad = false;
public:
    UlazniPodaci() {}

    void dodaj(T neobradjeni_podaci) {
        {
            unique_lock<mutex> lk(mtx);
            podaci.push(std::move(neobradjeni_podaci));
        }
        cv.notify_one();
    }

    bool preuzmi(T &neobradjeni_podaci) {
        unique_lock<mutex> lk(mtx);

        while(podaci.empty() && !zavrsen_rad)
            cv.wait(lk);

        if(podaci.empty()) return false;

        neobradjeni_podaci = std::move(podaci.front());
        podaci.pop();
        return true;
    }

    void zavrsi() {
        {
            unique_lock<mutex> lk(mtx);
            zavrsen_rad = true;
        }
        cv.notify_all();
    }
};


/** Klasa koja modeluje "postansko sanduce" izmedju radnika i pisaca.
*/
template<typename T>
class IzlazniPodaci {
private:
    queue<T> izlaz;
    mutex mtx;
    condition_variable cv;
    bool zavrsen_rad = false;
public:
    IzlazniPodaci() {}

    void dodaj(T obradjeni_podaci) {
        {
            unique_lock<mutex> lk(mtx);
            izlaz.push(std::move(obradjeni_podaci));
        }
        cv.notify_one();
    }

    bool preuzmi(T &obradjeni_podaci) {
        unique_lock<mutex> lk(mtx);

        while(izlaz.empty() && !zavrsen_rad)
            cv.wait(lk);

        if(izlaz.empty()) return false;

        obradjeni_podaci = std::move(izlaz.front());
        izlaz.pop();
        return true;
    }

   void zavrsi() {
        {
            unique_lock<mutex> lk(mtx);
            zavrsen_rad = true;
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
    string red;

    while(ulaz.preuzmi(red)) {
        unsigned id = 0;
        unsigned char komanda = 0;
        vector<double> ulazni = izdvoj_brojeve(red, id, komanda);

        izlazni_podaci trenutni_izlaz;
        trenutni_izlaz.id = id;
        trenutni_izlaz.komanda = komanda;
        trenutni_izlaz.ulazni = ulazni;

        vector<double> obradjeni;

        switch(trenutni_izlaz.komanda) {
            case 1: {
                size_t cnt = 0;
                for (size_t i = 0; i < ulazni.size(); ++i) {
                    if (i % 3 == 0 && ulazni[i] == std::trunc(ulazni[i])) {
                        long long v = static_cast<long long>(ulazni[i]);
                        if (v % 2 == 0) ++cnt;
                    }
                }
                obradjeni.push_back(static_cast<double>(cnt));
                break;
            }
            case 2: {
                double suma = 0.0; size_t n = 0;
                for (double x : ulazni)
                    if (x < 16.0 && x != std::trunc(x)) { suma += x; ++n; }
                if (n > 0) obradjeni.push_back(suma / n);
                break;
            }
            case 3: {
                vector<double> frac;
                frac.reserve(ulazni.size());
                for (double x : ulazni) if (x != std::trunc(x)) frac.push_back(x);
                if (!frac.empty()) {
                    double m = 0.0; for (double x : frac) m += x; m /= static_cast<double>(frac.size());
                    double s2 = 0.0; for (double x : frac) { double d = x - m; s2 += d*d; }
                    s2 /= static_cast<double>(frac.size());
                    obradjeni.push_back(s2);
                }
                break;
            }
            case 4: {
                for (size_t i = 0; i < ulazni.size(); ++i)
                    if (std::to_string(i).find('3') != string::npos)
                        obradjeni.push_back(ulazni[i]);
                break;
            }
            case 5: {
                for (double x : ulazni) {
                    if (x >= 0.0) {
                        double y = std::sqrt(x) + 4.0;
                        double g = x / 6.0 + 3.0;
                        if (y > g) obradjeni.push_back(y);
                    }
                }
                break;
            }
            default:
                trenutni_izlaz.validna_komanda = false;
                break;
        }
        
        trenutni_izlaz.obradjeni = std::move(obradjeni);
        izlaz.dodaj(trenutni_izlaz);
    }
}

/**
 * Logika citaca - nit koja radi citanje iz ulazne datoteke i salje u ulaznu
 * kolekciju za radnike
*/
void citac_nit(UlazniPodaci<string> &ulaz) {
    ifstream fin("ulaz.txt");

    if(!fin) {
        cerr << "Nismo uspeli da otvorimo fajl 'ulaz.txt'." << endl;
        ulaz.zavrsi();
        return;
    }

    string neobradjen_red;
    while(getline(fin, neobradjen_red)){
        if(!neobradjen_red.empty())
            ulaz.dodaj(neobradjen_red);
    }

    ulaz.zavrsi();
}

/**
 * Logika stampaca - nit koja radi pisanje u izlaznu datoteku podataka dobijenih
 * od radnika
*/
void stampac_nit(IzlazniPodaci<struct izlazni_podaci> &izlaz) {
    ofstream f_parni("parni.txt");
    ofstream f_neparni("neparni.txt");
    ofstream f_kanta("kanta.txt");

    if(!f_parni || !f_neparni || !f_kanta){
        cerr << "Nismo uspeli da otvorimo jedan od izlaznih fajlova." << endl;
        izlaz.zavrsi();
        return;
    }

    izlazni_podaci trenutni;
    while(izlaz.preuzmi(trenutni)){
        if(!trenutni.validna_komanda){
            f_kanta << trenutni.id << ":" << static_cast<unsigned>(trenutni.komanda);
            for(double x : trenutni.ulazni) f_kanta << ":" << x;
            f_kanta << "\n";
            continue;
        }

        if(trenutni.id % 2 == 0){
            f_parni << trenutni.id;
            for(double x : trenutni.obradjeni) f_parni << ":" << x;
            f_parni << "\n";
        } else {
            f_neparni << trenutni.id;
            for(double x : trenutni.obradjeni) f_neparni << ":" << x;
            f_neparni << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    UlazniPodaci<string> ulaz;
    IzlazniPodaci<izlazni_podaci> izlaz;

    thread nit_citac(citac_nit, std::ref(ulaz));
    
    thread radnici[BROJ_RADNIKA];
    for(int i = 0; i < BROJ_RADNIKA; i++)
        radnici[i] = thread(radnik_nit, std::ref(ulaz), std::ref(izlaz));
    
    thread nit_stampac(stampac_nit, std::ref(izlaz));


    nit_citac.join();
    
    for(int i = 0; i < BROJ_RADNIKA; i++) radnici[i].join();
    izlaz.zavrsi();

    nit_stampac.join();
 
    exit(0);
}