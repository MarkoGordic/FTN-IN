/*
    Napraviti konkurentni program koji pronalazi element najblizi 0 iz zadatog vektora brojeva.
    Posao podeliti u 3 niti. Vektor treba da sadrzi 900000 elemenata.
    Elementi su pseudoslucajni brojevi dobijeni pozivom funkcije rand().

    Za svaku nit, evidentirati trenutke kada je izvrsavanje pocelo i kada je zavrsilo.
    Na kraju programa, ispisati koliko je trajalo izvrsavanje svake niti.
*/

#include <iostream>
#include <thread>
#include <cmath>
#include <vector>
#include <random>

using namespace std;
using namespace chrono;

typedef vector<double>::const_iterator cit;

struct vreme {
    system_clock::time_point pocetak;
    system_clock::time_point kraj;
};

void f(cit pocetak, cit kraj, double & min, struct vreme * v) {
    v->pocetak = system_clock::now(); //evidentiramo trenutak kada je nit pocela da se izvrsava i upisemo u prosledjenu promenljivu v
    min = *pocetak; //proglasimo nulti element najblizim nuli
    for (auto it = pocetak + 1; it != kraj; it++) { //prodjemo kroz sve ostale elemente
        if (abs(*it) < abs(min)) //ako je i-ti element blizi nuli od trenutno najblizeg
            min = *it; //tada imamo novi najblizi element
    }

    v->kraj = system_clock::now();//trenutak kada je trazenje minimuma zavrseno upisujemo u prosledjenu promenljivu v
}

const int DUZINA = 900000;


int main() {
    int n = 3;
    int SEGMENT = DUZINA/n;
    default_random_engine gen;

    gen.seed(duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count());  // postavljamo seed random generatora na trenutno vreme sto bi trebalo da znaci da su brojevi zaista slucajni
    uniform_real_distribution<double> real_dist(-1e5, 1e5);

    vector<double> v(DUZINA);
    //punimo vektor pseudo-slucajnim brojevima
    for (int i = 0; i < DUZINA; i++) {
       v[i] = real_dist(gen);
    }

    double minimumi[n];  //niz elemenata najblizih nuli - svaki deo niza ce dati svoj element najblizi nuli
    struct vreme vremena[n]; //niz struktura u koju ce biti upisani podaci o trajanju izvrsavanja niti. Za svaku nit imamo poseban element u ovom nizu

    thread niti[n];
    //svaka nit dobija da nadje element najblizi nuli u jednoj trecini vektora.

    //iteratori na pocetak i kraj segmenta koji obradjuje svaka od niti, ovi iteratori se pomeraju kako se prolazi kroz razlicite niti
    cit pocetak = v.begin();
    cit kraj = v.begin() + SEGMENT;

    for (int i = 0; i < n; ++i) {
        niti[i] = thread(f, pocetak, kraj, ref(minimumi[i]), &vremena[i]);
        pocetak += SEGMENT;
        kraj += SEGMENT;
    }

    for (int i = 0; i < n; ++i) {
        niti[i].join();
    }

    //kada su sve niti zavrsile, imamo tri najbliza elementa u svakoj trecini niza.
    //Sada medju ta tri elementa, treba naci najblizi element
    double rez = minimumi[0];
    for (int i = 1; i < n; i++) {
       if (abs(minimumi[i]) < abs(rez))
            rez = minimumi[i];
    }

    cout << "Najblizi element nuli je: " << rez << endl;

    //ispis trajanja za svaku od niti
    for (int i = 0; i < n; i++) {
        duration<double, milli> trajanje = vremena[i].kraj - vremena[i].pocetak;
        cout << "Nit " << i+1 << " se izvrsavala " << trajanje.count() << " milisekundi. " << endl;
    }
}

