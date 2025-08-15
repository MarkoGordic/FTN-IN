#ifndef NITI_HPP
#define NITI_HPP

#include <thread>

#include "obracun.hpp"

using namespace std;

double izracunaj(list<string> kupljeno, map<string, double> cenovnik)
{
    double ukupna_cena;
    thread t(obracunajUkupno, kupljeno, cenovnik, ref(ukupna_cena));
    t.join();
    return ukupna_cena;
}

#endif // NITI_HPP
