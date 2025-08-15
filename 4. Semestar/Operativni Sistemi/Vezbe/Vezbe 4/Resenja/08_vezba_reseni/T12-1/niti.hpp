#ifndef NITI_HPP
#define NITI_HPP

#include <thread>
#include <vector>

#include "sabiranje.hpp"

using namespace std;

// Implementacija sabiranja korespondentnih elemenata celih vektora A i B pokretanjem onoliko niti koliko ima elemenata u vektorima
//
// a - Vektor A
// b - Vektor B
//
// Rezultat izvršavanja treba da bude vector<int> koji sadrži rezultat sabiranja korespondentnih elemenata.
//
vector<int> izracunaj(vector<int>& a, vector<int>& b)
{
    int duzina = a.size();
    vector<int> c(duzina);
    thread niti[duzina];

    for (int i = 0; i < duzina; ++i) {
        niti[i] = thread(saberiPar, a.begin()+i, b.begin()+i, c.begin()+i);
    }

    for (int i = 0; i < duzina; ++i) {
        niti[i].join();
    }

    return c;

}

#endif // NITI_HPP
