#ifndef ARTIKAL_HPP_INCLUDED
#define ARTIKAL_HPP_INCLUDED

#include "dinstring.hpp"
#include <iomanip>

class Artikal{
    private:
        DinString naziv;
        double cena;
        static int instanci;
    public:
        Artikal(const char[],const double);
        Artikal(const DinString&, const double);
        Artikal(const Artikal&);
        ~Artikal();

        friend ostream& operator<<(ostream& ,const Artikal&);
};

#endif // ARTIKAL_HPP_INCLUDED
