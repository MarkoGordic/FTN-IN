#ifndef PRAVOUGAONIK_DEF
#define PRAVOUGAONIK_DEF

#include "figura.hpp"

class Pravougaonik : public Figura
{
    private:
        double a, b;

    public:
        Pravougaonik(double aa = 3, double bb = 4)
        {
            a = aa;
            b = bb;
        }

        Pravougaonik(const Pravougaonik& rp)
        {
            a = rp.a;
            b = rp.b;
        }

        double getA() const
        {
            return a;
        }

        double getB() const
        {
            return b;
        }

        double getO() const
        {
            return 2 * (a + b);
        }

        double getP() const
        {
            return a * b;
        }
};

#endif
