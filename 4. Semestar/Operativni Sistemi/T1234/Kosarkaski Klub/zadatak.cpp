#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <thread>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <functional>

using namespace std;

#define BROJ_RADNIKA 3

class Kosarkas {
    private:
        int id;
        string ime_prezime;
        unsigned char komanda;
        vector<int> rezultati;
        vector<int> obradjeno;
    public:
        Kosarkas() {};
        Kosarkas(int id, string ime_prezime, unsigned char komanda, vector<int> rezultati){
            this->id = id;
            this->ime_prezime = ime_prezime;
            this->komanda = komanda;
            this->rezultati = rezultati;
        }

        void ispisi(ostream &out) {
            out << id << ":" << ime_prezime << ":" << (int)komanda;
            for(int x : obradjeno)
                out << ":" << x;
            out << endl;
        }

        int getID() { return id; }
        string getImePrezime() { return ime_prezime; }
        unsigned char getKomanda() { return komanda; }
        vector<int> getRezultati() { return rezultati; }
        vector<int> getObradjeno() { return obradjeno; }

        int setID(int id) { this->id = id; return id; }
        string setImePrezime(string ime_prezime) { this->ime_prezime = ime_prezime; return ime_prezime; }
        unsigned char setKomanda(unsigned char komanda) { this->komanda = komanda; return komanda; }
        vector<int> setRezultati(vector<int> rezultati) { this->rezultati = rezultati; return rezultati; }
        vector<int> setObradjeno(vector<int> obradjeno) { this->obradjeno = obradjeno; return obradjeno; }
};

template <typename T>
class UlazniPodaci {
    private:
        queue<T> podaci;
        mutex mtx;
        condition_variable cv;
        bool kraj;
    public:
        UlazniPodaci() { kraj = false; };

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

template <typename T>
class IzlazniPodaci {
    private:
        queue<T> podaci;
        mutex mtx;
        condition_variable cv;
        bool kraj;
    public:
        IzlazniPodaci() { kraj = false; };

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

void parsiraj_red(const string& ulaz, Kosarkas &podaci){
    istringstream ipodaci(ulaz);
    vector<int> brojevi;
    string tmp;

    if(getline(ipodaci, tmp, ':')) {
        podaci.setID(stoi(tmp));
    }
    if(getline(ipodaci, tmp, ':')) {
        podaci.setImePrezime(tmp);
    }
    if(getline(ipodaci, tmp, ':')) {
        podaci.setKomanda(static_cast<unsigned char>(stoul(tmp)));
    }
    while(getline(ipodaci, tmp, ',')) {
        brojevi.push_back(stoi(tmp));
    }

    podaci.setRezultati(brojevi);
}

void nit_radnik(UlazniPodaci<string> &ulaz, IzlazniPodaci<Kosarkas> &izlaz) {
    string trenutni_red;
    Kosarkas trenutni;
    vector<int> obradjeni;

    double prosek_ceo = 0;
    int prosek_trunc = 0;
    int br_utakmica_vece_prosek = 0;
    int max_rezultat = 0;

    while(ulaz.preuzmi(trenutni_red)) {
        obradjeni.clear();
        parsiraj_red(trenutni_red, trenutni);
        trenutni.setObradjeno(vector<int>{});

        switch(trenutni.getKomanda()) {
            case 1:
                prosek_ceo = 0;
                prosek_trunc = 0;
                br_utakmica_vece_prosek = 0;

                for(int x : trenutni.getRezultati())
                    prosek_ceo += x;
                
                prosek_trunc = trunc(prosek_ceo / trenutni.getRezultati().size());
                
                for(int x : trenutni.getRezultati()) if(x > prosek_trunc) br_utakmica_vece_prosek++;

                obradjeni.push_back(prosek_trunc);
                obradjeni.push_back(br_utakmica_vece_prosek);

                trenutni.setObradjeno(obradjeni);

                break;
            case 2:
                max_rezultat = 0;

                for(int x : trenutni.getRezultati())
                    if(x > max_rezultat) max_rezultat = x;

                obradjeni.push_back(max_rezultat);

                trenutni.setObradjeno(obradjeni);

                break;
            case 3: {
                vector<int> sortirano = trenutni.getRezultati();
                sort(sortirano.begin(), sortirano.end());
                trenutni.setObradjeno(sortirano);
                break;
            }
            default:
                break;
        }
        
        izlaz.dodaj(trenutni);
    }
}

void nit_citac(UlazniPodaci<string> &ulaz) {
    ifstream fulaz("kosarkasi.txt");

    if(!fulaz){
        cerr << "Programer ili OS je napunio gace. Nismo uspeli daotvorimo 'kosarkasi.txt'" << endl;
        ulaz.zavrsi();
        return;
    }

    string trenutni;
    while(getline(fulaz, trenutni)) {
        if(!trenutni.empty()) {
            ulaz.dodaj(trenutni);
        }
    }

    ulaz.zavrsi();
}

void nit_stampac(IzlazniPodaci<Kosarkas> &izlaz) {
    ofstream fizlaz("izvestaj.txt");

    if(!fizlaz){
        cerr << "OS ili programer su napunili gace bas jako, ili je kuci pregrizao kablove. Neuspesno otvaranje fajla." << endl;
        return;
    }

    Kosarkas trenutni;
    while(izlaz.preuzmi(trenutni)){
        trenutni.ispisi(fizlaz);
    }
}

int main() {
    UlazniPodaci<string> ulaz;
    IzlazniPodaci<Kosarkas> izlaz;

    thread citac(nit_citac, ref(ulaz));
    thread stampac(nit_stampac, ref(izlaz));
    thread radnici[BROJ_RADNIKA];
    for(int i = 0; i < BROJ_RADNIKA; i++)
        radnici[i] = thread(nit_radnik, ref(ulaz), ref(izlaz));

    citac.join();
    for(int i = 0; i < BROJ_RADNIKA; i++)
        radnici[i].join();
    izlaz.zavrsi();
    stampac.join();

    return 0;
}