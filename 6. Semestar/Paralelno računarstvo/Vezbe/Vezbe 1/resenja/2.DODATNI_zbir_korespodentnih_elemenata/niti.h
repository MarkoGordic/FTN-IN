#ifndef NITI_H_INCLUDED
#define NITI_H_INCLUDED

#include <vector>
#include <thread>

#include "suma_vektora.h"

using namespace std;

// v - vektor A čije elemente treba sumirati
// v - vektor B čije elemente treba sumirati
// povratna vrednost - suma korespondentnih elemenata vektora A i B, izračunata pozivanjem dve niti
vector<double> sumiraj(vector<double> a, vector<double> b) {
    vector<double> sum(a.size());
    thread t1(f,  a.begin(), a.begin() + a.size()/2,    // Stvaranje niti t1. Nit t1 sabira korespodendne elemente vektora a i b od a.begin() do a.begin() + a.size()/2.
                  b.begin(),
                  sum.begin()
    );
    thread t2(f,  a.begin() + a.size()/2,  a.end(),     // Stvaranje niti t2. Nit t2 sabira korespodendne elemente vektora a i b od a.begin() + a.size()/2 do a.end().
                  b.begin() + a.size()/2,
                  sum.begin() + a.size()/2
    );
    t1.join();
    t2.join();
    return sum;
}

#endif // NITI_H_INCLUDED
