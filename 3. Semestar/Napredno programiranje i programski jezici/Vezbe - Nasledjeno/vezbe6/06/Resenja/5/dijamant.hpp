#ifndef DIJAMANT_HPP_INCLUDED
#define DIJAMANT_HPP_INCLUDED

#include <iostream>
using namespace std;

class Dijamant {
    private:
        double vrednost;
        double karat;

    public:
        Dijamant() : vrednost(10000), karat(1) {}
        Dijamant(double v, double k) : vrednost(v), karat(k) {}
        Dijamant(const Dijamant& d) : vrednost(d.vrednost) , karat(d.karat) {}

        friend ostream& operator<<(ostream& out, const Dijamant &d) {
            out << "Dijamant: vrednost = " << d.vrednost << " karat = " << d.karat;
            return out;
        }
};

#endif // DIJAMANT_HPP_INCLUDED
