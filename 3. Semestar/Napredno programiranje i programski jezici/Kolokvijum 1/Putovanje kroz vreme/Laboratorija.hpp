#ifndef LABORATORIJA_HPP_INCLUDED
#define LABORATORIJA_HPP_INCLUDED
#include "VremenskaMasina.hpp"
#include "Putnik.hpp"

class Laboratorija
{
private:
    char naziv;
    VremenskaMasina masina;

public:
    Laboratorija():masina()
    {
        naziv='L';
    }
    
    Laboratorija(char naziv, int d, int t, StatusMasine s, bool i):masina(d,t,i,s)
    {
        this->naziv=naziv;
    }
    
    void pokreniEksperiment(Putnik& putnik)
    {
        masina.dodajPutnika(&putnik);
        masina.putuj();
    }
    
    friend void ispisiLaboratoriju(const Laboratorija& lab);
};



#endif // LABORATORIJA_HPP_INCLUDED
