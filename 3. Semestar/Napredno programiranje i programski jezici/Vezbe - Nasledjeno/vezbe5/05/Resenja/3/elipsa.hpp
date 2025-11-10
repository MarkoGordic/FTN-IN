#ifndef ELIPSA_DEF
#define ELIPSA_DEF

#include "figura.hpp"

class Elipsa : public Figura
{
    private:
        double x,y;

    public:
        Elipsa()
        {
            x = 2;
            y = 4;
        }

        Elipsa(double aa, double bb)
        {
            x = aa;
            y = bb;
        }

        Elipsa(const Elipsa& p)
        {
            x = p.x;
            y = p.y;
        }

        double getX() const
        {
            return x;
        }

        double getY() const
        {
            return y;
        }

        double getO() const
        {
            return M_PI * (3 * (x + y) - sqrt((3 * x + y) * (x + 3 * y)));
        }

        double getP() const
        {
            return M_PI * x * y;
        }
};

#endif

