#ifndef DETE_HPP_INCLUDED
#define DETE_HPP_INCLUDED

#include "putnik.hpp"

class PutnikDete : public Putnik
{
private:
    DinString mbRoditelja;
public:
    PutnikDete():Putnik(), mbRoditelja("1234546548135") {}
    PutnikDete(int bk, VrstaKarte vk, const DinString& maticniBroj, const DinString& imePutnika, const DinString& mbR): Putnik(bk, vk, maticniBroj, imePutnika), mbRoditelja(mbR) {}
    PutnikDete(const Putnik& p, const DinString& mbR): Putnik(p), mbRoditelja(mbR) {}

    DinString toString() const
    {
        DinString ret = "Dete: ";
        ret+=Putnik::toString();
        ret+="\nMatični broj roditelja: ";
        ret+=mbRoditelja;
        return ret;
    }
};

#endif // DETE_HPP_INCLUDED
