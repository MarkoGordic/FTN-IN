#ifndef OBLIK_HPP_INCLUDED
#define OBLIK_HPP_INCLUDED

#include "Pravougaonik.hpp"
#include "Elipsa.hpp"

class Oblik {
private:
    Pravougaonik A;
    Elipsa B;
public:
    Oblik(Pravougaonik a, Elipsa b) : A(a), B(b) {}
    double povrsina() const {
        return A.povrsina() + B.povrsina();
    }
    double obim() const {
        return A.obim() + B.obim();
    }
    void setA(Pravougaonik a) {
        A = a;
    }
    void setB(Elipsa b) {
        B = b;
    }
    Pravougaonik getA() const {
        return A;
    }
    Elipsa getB() const {
        return B;
    }
};

#endif // OBLIK_HPP_INCLUDED