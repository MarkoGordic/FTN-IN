#ifndef DIJAMANT_HPP_INCLUDED
#define DIJAMANT_HPP_INCLUDED

#include <iostream>
using namespace std;

class Dijamant {
private:
    double vrednost;
    double brojKarata;
public:
    Dijamant() : vrednost(0), brojKarata(0) {}
    Dijamant(double vrednost, double brojKarata) : vrednost(vrednost), brojKarata(brojKarata) {}
    Dijamant(const Dijamant& d) : vrednost(d.vrednost), brojKarata(d.brojKarata) {}

    friend std::ostream& operator<<(std::ostream& out, const Dijamant& d) {
        out << "Dijamant(" << d.vrednost << ", " << d.brojKarata << ")";
        return out;
    }
};

#endif // DIJAMANT_HPP_INCLUDED