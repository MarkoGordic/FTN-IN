#ifndef KVADRAT_DEF
#define KVADRAT_DEF

#include "pravougaonik.hpp"

class Kvadrat : public Pravougaonik
{
     public:
        Kvadrat() : Pravougaonik(3,3) {}
        Kvadrat(double aa) : Pravougaonik(aa,aa) {}
        Kvadrat(const Kvadrat& k) : Pravougaonik((Pravougaonik)k) {}
};

#endif
