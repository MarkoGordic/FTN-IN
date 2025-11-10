#ifndef PRAVOUGAONIK_HPP_INCLUDED
#define PRAVOUGAONIK_HPP_INCLUDED

#include "figura.hpp"

class Pravougaonik : public Figura {
protected:
    double x, y;
public:
    Pravougaonik () : Figura() {
        x = 2;
        y = 3;
    }

    Pravougaonik (double xx, double yy) : Figura() {
        x = xx;
        y = yy;
    }

    Pravougaonik (const Pravougaonik& p) : Figura() {
        x = p.x;
        y = p.y;
    }

    double getX () const { return x; }
    double getY () const { return y; }

    void setX (double xx) { x = xx; }
    void setY (double yy) { y = yy; }

    // realizacija apstraktnih metoda
    // sve dok ne definisemo obe funkcije kompajler ce javljati da je objekat apstraktan
    double getP () const { return x * y; }
    double getO () const { return 2 * ( x + y ); }
    // apstraktne liste su kao to do liste -> kad pravimo klase koje nasledjuju neku apstraktnu klasu,
    // ako ne izvedemo sve metode javljace nam se greska pa cemo znati da je neka metoda zaboravljena : )
};

#endif // PRAVOUGAONIK_HPP_INCLUDED
