#ifndef PROIZVODI_HPP
#define PROIZVODI_HPP

#include "dinstring.hpp"

class Proizvod {
protected:
    DinString naziv;
    int cena;
public:
        Proizvod(const DinString& n, int c) : naziv(n), cena(c) {}

        virtual void izracunajPopust() = 0;

        virtual void ispisi(){
            cout << "Naziv: " << naziv << endl;
            cout << "Cena: " << cena << endl;
        }

        int getCena() const {
            return cena;
        }

        DinString getNaziv() const {
            return naziv;
        }
};

#endif // PROIZVODI_HPP

