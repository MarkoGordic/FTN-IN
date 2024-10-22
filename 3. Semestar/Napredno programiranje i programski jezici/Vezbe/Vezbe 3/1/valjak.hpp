#ifndef VALJAK_HPP_INCLUDED
#define VALJAK_HPP_INCLUDED

#include "krug.hpp"
#include "pravougaonik.hpp"

class Valjak {
private:
    Krug baza;
    Pravougaonik omotac;

public:
    Valjak(double, double);
    double getR();
    double getH();
    double getV();
    double getP();
};

#endif // VALJAK_HPP_INCLUDED