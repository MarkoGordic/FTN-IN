#ifndef ELIPSA_HPP_INCLUDED
#define ELIPSA_HPP_INCLUDED

#include "figura.hpp"
#include <math.h>

class Elipsa : public Figura {
protected:
    double x, y;
public:
    Elipsa () : Figura() {
        x = 1;
        y = 2;
    }

    Elipsa (double xx, double yy) : Figura() {
        x = xx;
        y = yy;
    }

    Elipsa (const Elipsa& e) : Figura() {
        x = e.x;
        y = e.y;
    }

    double getX () const { return x; }
    double getY () const { return y; }

    void setX (double xx) { x = xx; }
    void setY (double yy) { y = yy; }

    // realizacija apstraktnih metoda
    // sve dok ne definisemo obe funkcije kompajler ce javljati da je objekat apstraktan
    double getP () const { return M_PI * ( 3 * (x + y) - sqrt( (3 * x + y) * (x + 3 * y) ) ); }
    double getO () const { return x * y * M_PI; }
};

#endif // ELIPSA_HPP_INCLUDED
