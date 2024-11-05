#ifndef TROUGAO_HPP_INCLUDED
#define TROUGAO_HPP_INCLUDED

#include <cmath>

class Trougao {
protected:
    double a, b, c;
public:
    Trougao(){
        a = 3;
        b = 4;
        c = 5;
    }

    Trougao(double aa, double bb, double cc){
        a = aa;
        b = bb;
        c = cc;
    }

    Trougao(const Trougao &t){
        a = t.a;
        b = t.b;
        c = t.c;
    }

    double obim() const {
        return a + b + c;
    }

    double povrsina() const {
        double s = obim() / 2;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }

    double getA() const {
        return a;
    }

    double getB() const {
        return b;
    }

    double getC() const {
        return c;
    }

    void setA(double aa){
        a = aa;
    }

    void setB(double bb){
        b = bb;
    }

    void setC(double cc){
        c = cc;
    }
};

#endif // TROUGAO_HPP_INCLUDED