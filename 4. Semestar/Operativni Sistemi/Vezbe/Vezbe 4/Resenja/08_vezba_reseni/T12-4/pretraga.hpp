#ifndef PRETRAGA_HPP
#define PRETRAGA_HPP

#include <cmath>
#include <vector>

using namespace std;

// Funkcija koja će biti iskorišćena kao funkcija niti - pretražuje ulaznu kolekciju (zadati su iteratori koji definišu granice pretrage) tražeći broj najbliži nuli.
//
// pocetak  - Iterator koji pokazuje na prvi element kolekcije koji učestvuje u pretrazi
// kraj     - Iterator iza poslednjeg elementa koji učestvuje u pretrazi
// najblizi - Nađeni element, najbliži nuli od svih elemenata koji su obuhvaćeni pretragom (izvršenjem funkcije ovaj broj se popuni)
//
void pretrazi(vector<double>::const_iterator pocetak, vector<double>::const_iterator kraj, double& najblizi)
{
    najblizi = *pocetak;
    for (auto it = pocetak; it != kraj; ++it) {
        if (fabs(*it) < fabs(najblizi)) {
            najblizi = *it;
        }
    }
}

#endif // PRETRAGA_HPP
