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
    if(n > v.size()) exit(-1);

    int korak = (v.size() / n) + 1;
    vector<double>::const_iterator it_poc;
    vector<double>::const_iterator it_kraj;

    vector<double> zbirovi;
    zbirovi.resize(n);

    for(int i = 0; i < n; i++){
        if(i == n-1)
            f(it_poc = v.begin() + i * korak, it_kraj = v.end(), zbirovi.at(i));
        else
            f(it_poc = v.begin() + i * korak, it_kraj = v.begin() + i * korak + korak, zbirovi.at(i));
    }

    double suma = 0;

    for(double el : zbirovi)
        suma += el;

    return suma;
}

#endif // NITI_H_INCLUDED
