#ifndef AUTOMOBIL_HPP_INCLUDED
#define AUTOMOBIL_HPP_INCLUDED

#include "menjac.hpp"
#include "skoljka.hpp"

class Automobil
{

private:
    Menjac m;
    Skoljka s;
public:
    Automobil() : m(), s() {}
    Automobil(TipMenjaca tm, int br, BojaSkoljke bs) : m(tm,br), s(bs) {}
    Automobil(const Automobil& a): m(a.m), s(a.s) {}

    bool setBrojBrzina(int br)
    {
        return m.setBrojBrzina(br);
    }

    void setBoja(BojaSkoljke bs)
    {
        s.setBoja(bs);
    }

    void setTipMenjaca(TipMenjaca tm)
    {
        m.setTip(tm);
    }

    int getBrojBrzina() const
    {
        return m.getBrojBrzina();
    }

    TipMenjaca getTipMenjaca() const
    {
        return m.getTip();
    }

    BojaSkoljke getBoja() const
    {
        return s.getBoja();
    }

    friend void ispisiAutomobil(const Automobil&);

};

#endif // AUTOMOBIL_HPP_INCLUDED
