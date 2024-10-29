#ifndef IGRA_HPP_INCLUDED
#define IGRA_HPP_INCLUDED

#include "Igrac.hpp"

enum TrenutnoStanje {NEPOZNAT_IGRAC, PROFIL_IGRACA, IGRA_RACUNAR, IGRA_PROTIVNIK};

class Igra {
private:
    Igrac igrac;
    TrenutnoStanje trenutnoStanje;

public:
    Igra(): igrac(), trenutnoStanje(NEPOZNAT_IGRAC) {}
    
    Igra(int brojPartija, int brojPoena, TrenutnoStanje stanjeIgre){
        igrac = Igrac(brojPoena, brojPartija);
        trenutnoStanje = stanjeIgre;
    }

    bool prijaviIgraca() {
        if(trenutnoStanje == NEPOZNAT_IGRAC) {
            trenutnoStanje = PROFIL_IGRACA;
            return true;
        }
        return false;
    }

    bool odjaviIgraca() {
        if(trenutnoStanje == PROFIL_IGRACA) {
            trenutnoStanje = NEPOZNAT_IGRAC;
            return true;
        }
        return false;
    }

    bool pocniIgruRacunar() {
        if((trenutnoStanje == PROFIL_IGRACA || trenutnoStanje == IGRA_PROTIVNIK) && igrac.getBrojPartija() + 1 <= 10) {
            trenutnoStanje = IGRA_RACUNAR;
            igrac.odigrajPartiju();
            return true;
        }
        return false;
    }

    bool pocniIgruOnline() {
        if((trenutnoStanje == PROFIL_IGRACA || trenutnoStanje == IGRA_RACUNAR) && igrac.getBrojPartija() + 1 <= 10) {
            trenutnoStanje = IGRA_PROTIVNIK;
            igrac.odigrajPartiju();
            return true;
        }
        return false;
    }

    bool pobedi(){
        if(trenutnoStanje == IGRA_RACUNAR) {
            igrac.dodajPoene(1);
            return true;
        } else if(trenutnoStanje == IGRA_PROTIVNIK) {
            igrac.dodajPoene(2);
            return true;
        }

        return false;
    }

    bool izgubi(){
        if(trenutnoStanje == IGRA_RACUNAR) {
            igrac.dodajPoene(-2);
            return true;
        } else if(trenutnoStanje == IGRA_PROTIVNIK) {
            igrac.dodajPoene(-2);
            return true;
        }

        return false;
    }

    bool ostvariBonus(){
        if(trenutnoStanje == IGRA_PROTIVNIK && igrac.getPoeni() >= 5) {
            int bonus = rand() % 3 + 1;
            igrac.dodajPoene(bonus);
            
            if(igrac.getPoeni() > 10) {
                igrac.setPoeni(10);
            }

            cout << "“Dobili ste dodatnih " << bonus << " poena" << endl;

            return true;
        }
        return false;
    }

    friend void ispisiIgru(const Igra& i);
};

#endif // IGRA_HPP_INCLUDED