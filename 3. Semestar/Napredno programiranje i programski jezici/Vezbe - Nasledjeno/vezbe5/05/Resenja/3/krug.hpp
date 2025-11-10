#ifndef KRUG_DEF
#define KRUG_DEF

#include "elipsa.hpp"

class Krug : public Elipsa {

    public:
        Krug() : Elipsa(2,2) {}
        Krug(double xx) : Elipsa(xx,xx) {}
        Krug(const Krug& k) : Elipsa((Elipsa)k) {}

};

#endif
