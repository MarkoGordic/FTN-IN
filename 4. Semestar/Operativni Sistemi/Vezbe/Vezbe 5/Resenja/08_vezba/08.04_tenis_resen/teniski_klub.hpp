#ifndef TENISKI_KLUB_HPP_INCLUDED
#define TENISKI_KLUB_HPP_INCLUDED

#include <mutex>
#include <condition_variable>

#include "podaci.hpp"
#include "mec.hpp"

#define MAX_TERENA 30

using namespace std;

class Teniski_klub {                             //Klasa deljenog resursa. Pravi se maksimalno 30 terena, ali ce u realnosti biti samo 3 terena.
private:
    Mec& mec;
    mutex mx;
    condition_variable uslovi[MAX_TERENA];  //Svaki teren ima svoju CV na kojoj igraci moraju cekati ako je teren zauzet.
    bool slobodni[MAX_TERENA];              //Svaki teren je ili slobodan ili zauzet, od cega zavisi i cekanje.
public:
    Teniski_klub(Mec& m, int ukupno_terena) : mec(m) {
        for (int i = 0; i < ukupno_terena; ++i)
            slobodni[i]= true;
    }

    // Metoda koju poziva nit koja simulira mec kako bi izvrsila teniski mec.
    // Metoda je blokirajuca - ako je zeljeni teren zauzet, izvrsenje ce blokirati dok se on ne oslobodi.
    //
    // broj_meca - Redni broj meca
    // na_terenu - Indeks terena na kojem mec treba da se odigra
    //
    // Potrebno je pozvati metodu mec.ceka kada je izabrani teren zauzet i mec mora da ceka.
    // Potrebno je pozvati metodu mec.pocinje kada se isprazni izabrani teren i mec moze da pocne.
    // Potrebno je pozvati metodu mec.zavrsen kada se mec zavrsi i mogu se proslediti izmereni vremenski intervali.
    void odigraj_mec(int broj_meca, int na_terenu) {   //Funkcija koju zove nit mec.
        Podaci p;
        {
            p.dosao = system_clock::now();       //Belezenje vremena moze van kriticne sekcije (nije deljeni resurs).
            unique_lock<mutex> lock(mx);
            while (!slobodni[na_terenu]) {           //Dogod je zauzet teren na kojem hocemo da igramo cekamo da se oslobodi.
                mec.ceka(broj_meca, na_terenu);
                uslovi[na_terenu].wait(lock);
            }
            p.pocetak = system_clock::now();
            slobodni[na_terenu] = false;         //Zauzimamo teren.
            mec.pocinje(broj_meca, na_terenu);
        }
        this_thread::sleep_for(seconds(rand()%5 + 1)); //Mec se igra do 5 sekundi. Za to vreme propusnica se oslobadja.
        p.trajanje = system_clock::now() - p.pocetak;
        mec.zavrsen(broj_meca, p);

        unique_lock<mutex> lock(mx);
        slobodni[na_terenu] = true;          //Teren se oslobadja.
        uslovi[na_terenu].notify_one();      //Obavestava se sledeci mec koji ceka na taj teren.
    }
};

#endif // TENISKI_KLUB_HPP_INCLUDED
