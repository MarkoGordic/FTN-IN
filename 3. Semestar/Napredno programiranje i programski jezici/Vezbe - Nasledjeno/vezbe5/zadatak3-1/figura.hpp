#ifndef FIGURA_HPP_INCLUDED
#define FIGURA_HPP_INCLUDED

// ne znamo koja je figura pa ne pisemo polja
// nekad moze apstraktna klasa imati polja i ne mora svaka metoda biti const
// moze sadrzati i neapstraktne metode
// apstraktna metoda nema telo!

class Figura {
public:
    virtual double getO () const = 0; // ne znamo formule za O i P pa je to 0
    virtual double getP () const = 0;
};

#endif // FIGURA_HPP_INCLUDED
