#ifndef NITI_H_INCLUDED
#define NITI_H_INCLUDED

#include <vector>
#include <thread>

#include "suma_vektora.h"

using namespace std;

// v - vektor čije elemente treba sumirati
// n - koliko niti treba pokrenuti
// povratna vrednost - suma svih elemenata vektora, izračunata pokretanjem n niti (svaka nit treba da obradi jedan deo elemenata)
double sumiraj(vector<double> v, int n) {
    double zbir[n];
    ci begin = v.begin();                      //Iterator na pocetak vektora.
    ci end = begin + v.size()/n;               //Iterator na kraj prvog dela vektora. Vektor se deli na N delova, pri cemu je kraj prvog dela na begin + v.size()/n.
    thread t[n];                               //Niz od N niti (objekata niti).
    for(int i = 0; i<n-1; ++i) {
        t[i] = thread(f, begin, end,  ref(zbir[i]));  //Svaka nit uzima pocetak i kraj svog dela vektora (iteratore) kao i jedan od zbirova iz niza zbirova.
        begin = end;                                  //Pocetak sledeceg dela vektora koji se obradjuje je kraj prethodnog dela.
        end += v.size()/n;                            //Kraj sledeceg dela vektora koji se obradjuje je kraj prethodnog dela + v.size()/n.
    }
    t[n-1] = thread(f, begin, v.end(),  ref(zbir[n-1]));     //Posebno izdvojen zadnji zbir (deo vektora). Ovo se radi iz razloga sto broj elemenata vektora ne mora biti deljiv
                                                            //sa brojem niti. Npr. 10/3, pa moramo da odvojimo i posebno obradimo zadnji deo vektora. U 10/3 verziji prve
                                                            //2 niti bi obradjivale po 3 elementa vektora a zadnja nit 4.
    for(int i = 0; i<n; ++i) {
        t[i].join();                                          //Cekanje niti main da se sve niti niza niti t zavrse.
    }
    double z = 0;
    for(int i = 0; i<n; ++i) {                            //Ispis pojedinacnih zbirova svih niti i spajanje konacnog zbira.
        cout << "zbir[" << i << "] = " << zbir[i] << endl;
        z += zbir[i];
    }
    return z;
}

#endif // NITI_H_INCLUDED
