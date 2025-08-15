#ifndef OBRTANJE_HPP
#define OBRTANJE_HPP

#include <list>

using namespace std;

// Implementacija obrtanja redosleda elemenata u listi
// Ova funkcija treba da bude iskorišćena za funkciju niti koje ovaj program pokreće.
//
// ulazna  - Ulazna lista, koja se obrađuje
// izlazna - Rezultujuća lista (biće popunjena elementima u obrnutom redosledu)
//
void obrniRedosled(const list<int>& ulazna, list<int>& izlazna)
{
    // Ocekuje se da je izlazna lista prazna
    for (auto it = ulazna.begin(); it != ulazna.end(); ++it) {
        izlazna.push_front(*it);
    }
}

#endif // OBRTANJE_HPP
