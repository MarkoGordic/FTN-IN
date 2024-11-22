#ifndef TELEFON_HPP_INCLUDED
#define TELEFON_HPP_INCLUDED

#include "dinstring.hpp"

class Telefon {
protected:
    DinString broj;
public:
    Telefon() : broj("") {}
    Telefon(DinString broj) : broj(broj) {}
    Telefon(const Telefon &t) : broj(t.broj) {}

    bool pozovi(DinString broj) {
        if (this->broj != broj) {
            return true;
        }
        return false;
    }

    DinString getBroj() const {
        return broj;
    }
};

#endif // TELEFON_HPP_INCLUDED