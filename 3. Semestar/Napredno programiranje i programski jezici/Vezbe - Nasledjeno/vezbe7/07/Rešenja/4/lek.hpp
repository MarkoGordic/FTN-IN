#ifndef LEK_HPP_INCLUDED
#define LEK_HPP_INCLUDED

#include "artikal.hpp"
#include "dinstring.hpp"

class Lek : public Artikal {
    private:
        long jkl;
        DinString naziv;
        double jedinicnaCena;
        int kolicina;

    public:
        Lek() : jkl(0), naziv(""), jedinicnaCena(0), kolicina(0) {}

        Lek(long pJkl, const char pNaziv[], double pJedinicnaCena, int pKolicina) : jkl(pJkl), naziv(pNaziv), jedinicnaCena(pJedinicnaCena), kolicina(pKolicina) {}

        Lek(long pJkl, const DinString& pNaziv, double pJedinicnaCena, int pKolicina) : jkl(pJkl), naziv(pNaziv), jedinicnaCena(pJedinicnaCena), kolicina(pKolicina) {}

        Lek(const Lek& l) : jkl(l.jkl), naziv(l.naziv), jedinicnaCena(l.jedinicnaCena), kolicina(l.kolicina) {}

        double getVrednost() const {
            return jedinicnaCena * kolicina;
        }

        friend ostream& operator<<(ostream& out, const Lek& lek) {
            out << "LEK [ jkl: " << lek.jkl << ", n: " << lek.naziv << ", jc: " << lek.jedinicnaCena << ", kol: " << lek.kolicina << " ]";
            return out;
        }
};

#endif // LEK_HPP_INCLUDED
