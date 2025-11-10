#ifndef OBLIK_DEF
#define OBLIK_DEF

#include "pravougaonik.hpp"
#include "elipsa.hpp"

class Oblik
{
    protected:
        Pravougaonik A;
        Elipsa B;

    public:
        Oblik(double aa = 5, double bb = 3) : A(aa, bb), B(aa / 2, bb / 2) {}

        Oblik(const Oblik& oblik) : A(oblik.A), B(oblik.B) {}

        const double getP() const
        {
            return A.getP() - B.getP();
        }

        const double getO() const
        {
            return A.getO() + B.getO();
        }
};

#endif
