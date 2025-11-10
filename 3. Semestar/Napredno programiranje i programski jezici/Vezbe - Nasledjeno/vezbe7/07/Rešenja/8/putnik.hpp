#ifndef PUTNIK_HPP_INCLUDED
#define PUTNIK_HPP_INCLUDED

#include "dinstring.hpp"
#include "karta.hpp"

class Putnik
{
protected:
    Karta karta;
    DinString mb, ime;
public:
    Putnik():karta(), mb("2323232323231"), ime("Vanja Milinkovic Savic") {}
    Putnik(int bk, VrstaKarte vk, const DinString& maticniBroj, const DinString& imePutnika): karta(bk, vk), mb(maticniBroj), ime(imePutnika) {}

    DinString getMb() const
    {
        return mb;
    }
    VrstaKarte getVrstaKarte() const
    {
        return karta.getVrstaKarte();
    }

    virtual DinString toString() const
    {
        return ime + " " + mb;
    }

    friend ostream& operator<<(ostream& os, const Putnik& p)
    {
        os << p.toString() << endl;
        os << p.karta << endl;
        return os;
    }
};

#endif // PUTNIK_HPP_INCLUDED
