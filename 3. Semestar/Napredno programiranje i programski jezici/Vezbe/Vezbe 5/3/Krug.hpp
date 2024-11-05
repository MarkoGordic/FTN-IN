#ifndef KRUG_HPP_INCLUDED
#define KRUG_HPP_INCLUDED

#include "Elipsa.hpp"

class Krug : public Elipsa {
public:
    Krug() : Elipsa(3,3) {}
    Krug(double a) : Elipsa(a,a) {}
    Krug(const Krug &k) : Elipsa(k.a,k.b) {}
};

#endif // KRUG_HPP_INCLUDED