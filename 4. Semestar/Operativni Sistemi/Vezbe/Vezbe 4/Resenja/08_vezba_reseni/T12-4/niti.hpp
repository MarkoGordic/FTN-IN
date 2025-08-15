#ifndef NITI_HPP
#define NITI_HPP

#include <thread>
#include <vector>

#include "pretraga.hpp"

using namespace std;

// Implementacija pokretanja tri niti koje treba da pretraže (svaka svoju trećinu) ulazni vektor brojeva i nađu element najbliži nuli
//
// ulaz - Ulazni vektor brojeva koji se pretražuje
//
// Povratna vrednost je nađeni element, najbliži nuli od svih elemenata koji su obuhvaćeni pretragom
//
double izracunaj(vector<double> ulaz)
{
    // Uvek treba napraviti 3 niti i podrazumeva se da je broj elemenata vektora deljiv sa 3
    int brojNiti = 3;
    thread niti[brojNiti];
    vector<double> najblizi(brojNiti);
    int korak = ulaz.size() / brojNiti;

    for (int i = 0; i < brojNiti; ++i) {
        niti[i] = thread(pretrazi, ulaz.begin() + i*korak, ulaz.begin() + (i+1)*korak, ref(najblizi[i]));
    }

    for (int i = 0; i < brojNiti; ++i) {
        niti[i].join();
    }

    double rezultat;
    pretrazi(najblizi.begin(), najblizi.end(), rezultat);

    return rezultat;

}


#endif // NITI_HPP
