#ifndef KOCKA_H_INCLUDED
#define KOCKA_H_INCLUDED

#include <iostream>
#include <cstdlib> // srand, rand
#include <ctime> // time

using namespace std;

class Kocka{
    private:
        int vrednost;
    public:
        Kocka() { vrednost = 1; }

        Kocka(int i) { vrednost = i; } //pretpostavljamo da ce vrednost parametra biti validna vrednost (1..6)

        Kocka(const Kocka &k) { vrednost = k.vrednost; }

        void baci() { vrednost = rand() % 6 + 1; }

        int getVrednost() const { return vrednost; }
};

#endif // KOCKA_H_INCLUDED
