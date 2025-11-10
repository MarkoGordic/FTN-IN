#ifndef KRUG_HPP_INCLUDED
#define KRUG_HPP_INCLUDED

#include <cmath>

class Krug {
private:
    double r;
public:
    Krug(double rr = 1){ // kada imamo konstruktor sa podrazumevanim parametara treba ga na oba nacina pozvati
        r = rr;
    }
    double getR() const {
        return r;
    }
    double getO() const {
        return 2 * r * M_PI;
    }
    double getP() const {
        return r * r * M_PI;
    }
};

#endif // KRUG_HPP_INCLUDED
