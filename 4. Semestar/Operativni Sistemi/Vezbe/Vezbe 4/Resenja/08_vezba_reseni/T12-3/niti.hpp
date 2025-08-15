#ifndef NITI_HPP
#define NITI_HPP

#include <thread>
#include <list>

#include "obrtanje.hpp"

using namespace std;

// Implementacija obrtanja redosleda elemenata u listi pokretanjem jedne nove niti
//
// ulazna  - Ulazna lista, koja se obrađuje
//
// Rezultat je rezultujuća lista (popunjena elementima u obrnutom redosledu)
//
list<int> izracunaj(const list<int>& ulazna)
{
    list<int> izlazna;
    thread t(obrniRedosled, ref(ulazna), ref(izlazna));
    t.join();
    return izlazna;
}

#endif // NITI_HPP
