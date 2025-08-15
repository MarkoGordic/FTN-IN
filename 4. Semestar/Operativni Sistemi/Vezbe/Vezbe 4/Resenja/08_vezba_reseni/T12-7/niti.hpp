#ifndef NITI_HPP
#define NITI_HPP

#include <thread>
#include <vector>

#include "logicko_kolo.hpp"

using namespace std;

// Implementacija operacije XOR nad ulaznim vektorima A i B izvršene uz pomoć dve niti (svaka nit obrađuje polovinu)
//
// a - Vektor A (16 binarnih cifara)
// b - Vektor B (16 binarnih cifara)
//
// Rezultat izvršavanja treba da bude vector<int> koji sadrži rezultat izvršenja XOR operacije nad ulaznim vektorima.
//
vector<int> izracunaj(vector<int>& a, vector<int>& b)
{
    // Duzine ulaznih vektora su uvek 16
    vector<int> c(16);

    thread t1(izvrsiXOR, a.begin(), a.begin() + 8, b.begin(), c.begin());
    thread t2(izvrsiXOR, a.begin() + 8, a.end(), b.begin() + 8, c.begin() + 8);

    t1.join();
    t2.join();

    return c;
}

#endif // NITI_HPP
