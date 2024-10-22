#include "pravougaonik.hpp"

Pravougaonik::Pravougaonik() {
    a = 1;
    b = 1;
}

Pravougaonik::Pravougaonik(double a, double b) {
    this->a = a;
    this->b = b;
}

double Pravougaonik::getA() {
    return a;
}

double Pravougaonik::getB() {
    return b;
}

double Pravougaonik::getO() {
    return 2 * (a + b);
}

double Pravougaonik::getP() {
    return a * b;
}