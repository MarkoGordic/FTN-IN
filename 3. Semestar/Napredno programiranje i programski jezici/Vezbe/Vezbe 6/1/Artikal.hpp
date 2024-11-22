#ifndef ARTIKAL_HPP_INCLUDED
#define ARTIKAL_HPP_INCLUDED

#include <iostream>
#include "dinstring.hpp"

class Artikal {
private:
    DinString naziv;
    double cena;
    static int instanci;
public:
    Artikal(const char n[], const double c) : naziv(n) {
        cena = c;
        instanci++;
    }

    Artikal(const DinString& n, const double c) : naziv(n), cena(c) {
        instanci++;
    }

    Artikal(const Artikal& a) : naziv(a.naziv), cena(a.cena) {
        instanci++;
    }

    int getInstanci() const {
        return instanci;
    }

    ~Artikal() {
        instanci--;
    }

    friend std::ostream& operator<<(std::ostream& out, const Artikal& a) {
        out << "Naziv: " << a.naziv << ", Cena: " << a.cena;
        return out;
    }
};

int Artikal::instanci = 0;

#endif // ARTIKAL_HPP_INCLUDED
