#ifndef ELIPSA_HPP_INCLUDED
#define ELIPSA_HPP_INCLUDED

#include "Figura.hpp"
#include <cmath>

class Elipsa : public Figura {
protected:
    double a, b;
public:
    Elipsa() : a(3), b(4) {}
    Elipsa(double aa, double bb) : a(aa), b(bb) {}
    Elipsa(const Elipsa &e) : a(e.a), b(e.b) {}

    double obim() const {
        return 3.14159 * (3 * (a + b) - sqrt((3 * a + b) * (a + 3 * b)));
    }

    double povrsina() const {
        return 3.14159 * a * b;
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

#endif // ELIPSA_HPP_INCLUDED