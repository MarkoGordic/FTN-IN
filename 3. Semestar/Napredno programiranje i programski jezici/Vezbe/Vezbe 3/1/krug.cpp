#include "krug.hpp"

Krug::Krug() {
    r = 1;
}

Krug::Krug(double r = 1) {
    this->r = r;
}

double Krug::getR() {
    return r;
}

double Krug::getO() {
    return 2 * r * 3.14;
}

double Krug::getP() {
    return r * r * 3.14;
}