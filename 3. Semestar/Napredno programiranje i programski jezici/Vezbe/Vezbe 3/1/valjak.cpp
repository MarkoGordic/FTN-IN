#include "valjak.hpp"

Valjak::Valjak(double r, double b): baza(r), omotac(2*r*3.14, b){}

double Valjak::getR(){
    return baza.getR();
}

double Valjak::getH(){
    return omotac.getB();
}

double Valjak::getV(){
    return omotac.getB() * baza.getR();
}

double Valjak::getP(){
    return 2 * baza.getP() + omotac.getP();
}