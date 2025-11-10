#ifndef VALJAK_HPP_INCLUDED
#define VALJAK_HPP_INCLUDED

#include <cmath>
// ne moramo include za krug.hpp i pravougaonik.hpp jer su oni vec u main
// ali pod uslovom da su prvo dodati krug.hpp i pravougaonik.hpp pre valjak.hpp
// doduse nije greska ako ih opet include ovde :3

class Valjak {
private:
    Krug B;
    Pravougaonik M;
public:
    Valjak (double r = 3, double H = 5) : B(r), M(2 * r * M_PI, H) {}
    // inicijalizator, koristimo za slozene objekte
    // dok prosta polja radimo kao i do sada :)

    double getR() const {
        return B.getR();
    }
    double getH() const {
        return M.getB();
    }
    double getP() const {
        return M.getP() + 2 * B.getP();
    }
    double getV() const {
        return B.getP() * getH(); // ali moze i M.getB() umesto getH()
    }
};

#endif // VALJAK_HPP_INCLUDED
