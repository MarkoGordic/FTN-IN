#ifndef PRAVILAN_OBLIK_HPP_INCLUDED
#define PRAVILAN_OBLIK_HPP_INCLUDED

#include "Oblik.hpp"

class PravilanOblik : public Oblik {
public:
    PravilanOblik(Pravougaonik a, Elipsa b) : Oblik(a, b) {
        if (a.getA() != a.getB()) {
            throw std::invalid_argument("Pravougaonik nije kvadrat.");
        }
        if (b.getA() != b.getB()) {
            throw std::invalid_argument("Elipsa nije krug.");
        }
    }

    double povrsina() const {
        return Oblik::getA().povrsina() + Oblik::getB().povrsina();
    }

    double obim() const {
        return Oblik::getA().obim() + Oblik::getB().obim();
    }
};

#endif // PRAVILAN_OBLIK_HPP_INCLUDED