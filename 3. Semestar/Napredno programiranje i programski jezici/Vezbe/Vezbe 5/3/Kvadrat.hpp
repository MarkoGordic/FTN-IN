#ifndef KVADRAT_HPP_INCLUDED
#define KVADRAT_HPP_INCLUDED

#include "Pravougaonik.hpp"

class Kvadrat : public Pravougaonik {
public:
    Kvadrat() : Pravougaonik(3,3) {}
    Kvadrat(double aa) : Pravougaonik(aa,aa) {}
    Kvadrat(const Kvadrat &k) : Pravougaonik(k.a,k.b) {}
};

#endif // KVADRAT_HPP_INCLUDED