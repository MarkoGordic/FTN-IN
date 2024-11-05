#ifndef OBLIK_HPP_INCLUDED
#define OBLIK_HPP_INCLUDED

#include "Kvadrat.hpp"
#include "Krug.hpp"

class Oblik {
private:
    Kvadrat A;
    Krug B;
public:
    Oblik() : A(), B() {}
    Oblik(double aa, double bb) : A(aa), B(bb) {}
    Oblik(const Oblik &o) : A(o.A), B(o.B) {}

    double obim() const {
        return A.obim() + B.obim();
    }

    double povrsina() const {
        return A.povrsina() + B.povrsina();
    }

    double getA() const {
        return A.getA();
    }

    double getB() const {
        return B.getA();
    }

    void setA(double aa){
        A.setA(aa);
        A.setB(aa);
    }

    void setB(double bb){
        B.setA(bb);
        B.setB(bb);
    }
};

#endif // OBLIK_HPP_INCLUDED