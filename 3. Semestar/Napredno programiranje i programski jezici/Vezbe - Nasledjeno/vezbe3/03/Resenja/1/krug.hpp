#ifndef KRUG_HPP_INCLUDED
#define KRUG_HPP_INCLUDED

#include <cmath>
// ili
//#define M_PI 3.14

class Krug {
    private:
        double r;
    public:
        Krug(double rr = 1){
            r = rr;
        }

        double getR() const{
            return r;
        }

        double getO() const{
            return 2 * r * M_PI;
        }

        double getP() const{
            return r * r * M_PI;
        }
};

#endif // KRUG_HPP_INCLUDED
