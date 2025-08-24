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
        queue<T> podaci;
        mutex mtx;
        condition_variable cv;
        bool kraj;
    public:
        UlazniPodaci() { kraj = false; }

        void dodaj(T neobradjeni_podaci) {
            {
                unique_lock<mutex> lk(mtx);
                podaci.push(neobradjeni_podaci);
            }

            cv.notify_one();
        }

        bool preuzmi(T &neobradjeni_podaci) {
            unique_lock<mutex> lk(mtx);

            while(!kraj && podaci.empty())
                cv.wait(lk);

            if(podaci.empty()) return false;

            neobradjeni_podaci = podaci.front();
            podaci.pop();
            return true;
        }

        void zavrsi() {
            {
                unique_lock<mutex> lk(mtx);
                kraj = true;
            }

            cv.notify_all();
        }
};

template<typename T>
class IzlazniPodaciPlejlista {
    private:
        queue<T> podaci;
        mutex mtx;
        condition_variable cv;
        bool kraj;
    public:
        IzlazniPodaciPlejlista() { kraj = false; }

        void dodaj(T obradjeni_podaci) {
            {
                unique_lock<mutex> lk(mtx);
                podaci.push(obradjeni_podaci);
            }

            cv.notify_one();
        }

        bool preuzmi(T &obradjeni_podaci) {
            unique_lock<mutex> lk(mtx);

            while(!kraj && podaci.empty())
                cv.wait(lk);

            if(podaci.empty()) return false;

            obradjeni_podaci = podaci.front();
            podaci.pop();
            return true;
        }

        void zavrsi() {
            {
                unique_lock<mutex> lk(mtx);
                kraj = true;
            }
            
            cv.notify_all();
        }
};

class IzlazniPodaciPoruka {
    private:
        queue<DeoPoruke> podaci;
        mutex mtx;
        condition_variable cv;
        bool kraj;
    public:
        IzlazniPodaciPoruka() { kraj = false; }

        void dodaj(DeoPoruke obradjeni_podaci) {
            {
                unique_lock<mutex> lk(mtx);
                podaci.push(obradjeni_podaci);
            }

            cv.notify_one();
        }

        bool preuzmi(DeoPoruke &obradjeni_podaci) {
            unique_lock<mutex> lk(mtx);

            while(!kraj && podaci.empty())
                cv.wait(lk);

            if(podaci.empty()) return false;

            obradjeni_podaci = podaci.front();
            podaci.pop();
            return true;
        }

        void zavrsi() {
            {
                unique_lock<mutex> lk(mtx);
                kraj = true;
            }

            cv.notify_all();
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
            case 0:
                pesma.ime_pesme = polje;
                break;
            case 1:
                pesma.ime_autora = polje;
                break;
            case 2:
                pesma.duzina = stoi(polje);
                break;
            case 3:
                pesma.kljuc = stoi(polje);
                break;
            case 4:
                pesma.id_kljuca = stoi(polje);
                break;
            case 5:
                pesma.ime_albuma = polje;
                break;
        }

        prethodna_pozicija = pozicija + 1;
        broj_polja++;
    }

    if(prethodna_pozicija < neobradjeni_podaci.length()) {
        string polje = neobradjeni_podaci.substr(prethodna_pozicija);
        pesma.id = stoi(polje);
    }

   return pesma;
}

void radnik_nit(UlazniPodaci<string> &ulaz, IzlazniPodaciPlejlista<struct Pesma> &izlaz_plejlista, IzlazniPodaciPoruka &izlaz_poruka){
    string red;

    while(ulaz.preuzmi(red)){
        Pesma trenutna;
        trenutna = obradi_pesmu(red);

        int index;
        char trazeni_karakter;
        DeoPoruke novi_deo;

        if(trenutna.id % 3 == 0){
            if(trenutna.ime_pesme.length() < trenutna.kljuc)
                index = trenutna.kljuc % trenutna.ime_pesme.length();
            else
                index = trenutna.kljuc;

            if(trenutna.id_kljuca == 20)
                cout << trenutna.ime_pesme << " " << trenutna.kljuc;
            trazeni_karakter = trenutna.ime_pesme[index];
        }

        if(trenutna.id % 3 == 0 && trenutna.id % 2 == 0){
            novi_deo.id_kljuca = trenutna.id_kljuca;
            novi_deo.karakter = trazeni_karakter;

            izlaz_plejlista.dodaj(trenutna);
            izlaz_poruka.dodaj(novi_deo);
        } else if(trenutna.id % 3 == 0){
            novi_deo.id_kljuca = trenutna.id_kljuca;
            novi_deo.karakter = trazeni_karakter;
            izlaz_poruka.dodaj(novi_deo);
        } else if(trenutna.id % 2 == 0)
            izlaz_plejlista.dodaj(trenutna);
    }
}

void citac_nit(UlazniPodaci<string> &ulaz) {
    ifstream fin(ULAZNA_DATOTEKA);

    if(!fin) {
        cerr << "Doslo je do greske! Nismo uspeli da otvorimo ulaznu datoteku." << endl;
        ulaz.zavrsi();
        return;
    }

    string trenutni_red;

    while(getline(fin, trenutni_red)){
        if(!trenutni_red.empty())
            ulaz.dodaj(trenutni_red);
    }

    // https://en.cppreference.com/w/cpp/io/basic_ifstream/close.html
    // This function is called by the destructor of basic_ifstream when the stream object goes out of scope and is not usually invoked directly.
    ulaz.zavrsi();
}

void stampac_plejliste_nit(IzlazniPodaciPlejlista<struct Pesma> &izlaz_plejlista) {
    ofstream fout("plejlista_parni.txt");

    if(!fout){
        cerr << "Doslo je do greske prilikom otvaranja izlaznog fajla." << endl;
        return;
    }

    Pesma trenutna_pesma;
    while(izlaz_plejlista.preuzmi(trenutna_pesma)){
        fout << trenutna_pesma.ime_pesme << " - " << trenutna_pesma.ime_autora << " " << trenutna_pesma.duzina << " " << trenutna_pesma.kljuc << " " << trenutna_pesma.id_kljuca << " " << trenutna_pesma.ime_albuma << " " << trenutna_pesma.id << endl;
    }
}

void stampac_poruke_nit(IzlazniPodaciPoruka &izlaz_poruka) {
    ofstream fout(IZLAZ_DATOTEKA_PORUKA);

    if(!fout){
        cerr << "Doslo je do greske prilikom otvaranja izlaznog fajla." << endl;
        return;
    }

    vector<DeoPoruke> poruka;
    {
        DeoPoruke trenutni;
        while(izlaz_poruka.preuzmi(trenutni)){
            poruka.push_back(trenutni);
        }
    }

    sort(poruka.begin(), poruka.end(), [](const DeoPoruke &a, const DeoPoruke &b) {
        return a.id_kljuca < b.id_kljuca;
    });

    for(const auto &deo : poruka) {
        fout << deo.karakter;
    }
}

int main() {
    UlazniPodaci<string> ulazni_podaci;
    IzlazniPodaciPlejlista<Pesma> izlazni_podaci_plejlista;
    IzlazniPodaciPoruka izlazni_podaci_poruka;

    thread nit_citac(citac_nit, ref(ulazni_podaci));
    thread radnici[BROJ_RADNIKA];
    for(int i = 0; i < BROJ_RADNIKA; i++)
        radnici[i] = thread(radnik_nit, ref(ulazni_podaci), ref(izlazni_podaci_plejlista), ref(izlazni_podaci_poruka));
    thread nit_stampac_plejlista(stampac_plejliste_nit, ref(izlazni_podaci_plejlista));
    thread nit_stampac_poruka(stampac_poruke_nit, ref(izlazni_podaci_poruka));

    nit_citac.join();

    for(int i = 0; i < BROJ_RADNIKA; i++)
        radnici[i].join();

    izlazni_podaci_plejlista.zavrsi();
    izlazni_podaci_poruka.zavrsi();

    nit_stampac_plejlista.join();
    nit_stampac_poruka.join();

    return 0;
}