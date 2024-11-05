#ifndef PRAVOUGAONIK_HPP_INCLUDED
#define PRAVOUGAONIK_HPP_INCLUDED

#include "Figura.hpp"

class Pravougaonik : public Figura {
protected:
    double a, b;
public:
    Pravougaonik() : a(3), b(4) {}
    Pravougaonik(double aa, double bb) : a(aa), b(bb) {}
    Pravougaonik(const Pravougaonik &p) : a(p.a), b(p.b) {}

    double obim() const {
        return 2 * a + 2 * b;
    }

    double povrsina() const {
        return a * b;
    }

    double getA() const {
        return a;
    }

    double getB() const {
        return b;
    }

    void setA(double aa){
        a = aa;
    }

    void setB(double bb){
        b = bb;
    }
};

#endif // PRAVOUGAONIK_HPP_INCLUDED