#ifndef NITI_HPP
#define NITI_HPP

#include <thread>
#include <list>

#include "ispis.hpp"

using namespace std;

// Implementacija pokretanja više niti koje treba da ispišu svoje redne brojeve (koristeći funkciju "ispisi")
//
// brojNiti - Broj niti koje je potrebno startovati
//
void izracunaj(int brojNiti)
{
	thread niti[brojNiti];

	for (int i = 0; i < brojNiti; ++i) {
        niti[i] = thread(ispisi, i+1);
	}

	for (int i = 0; i < brojNiti; ++i) {
        niti[i].join();
	}

}

#endif // NITI_HPP
