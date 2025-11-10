#ifndef IGRA_HPP_INCLUDED
#define IGRA_HPP_INCLUDED
#include "igrac.hpp"
#include <cstdlib>

enum StanjeIgre{NEPOZNAT_IGRAC, PROFIL_IGRACA, IGRA_RACUNAR, IGRA_PROTIVNIK};
class Igra{
private:
    Igrac i;
    StanjeIgre trenutnoStanje;
public:
    Igra():i(), trenutnoStanje(NEPOZNAT_IGRAC){} //Pozivamo KBP za igraca a on postavlja vrednosti za broj poena i partije na 0
    Igra(int p, int bp, StanjeIgre si):i(bp, p), trenutnoStanje(si) {}

    bool prijaviIgraca(){
        if(trenutnoStanje == NEPOZNAT_IGRAC){
            trenutnoStanje = PROFIL_IGRACA;
            return true;
        }
        return false;
    }

    bool odjaviIgraca(){
        if(trenutnoStanje == PROFIL_IGRACA){
            trenutnoStanje = NEPOZNAT_IGRAC;
            i.resetuj();
            return true;
        }
        return false;
    }

    bool pocniIgruRacunar(){
        if((trenutnoStanje == PROFIL_IGRACA || trenutnoStanje == IGRA_PROTIVNIK) && i.getBrojPartija()+1<=10){
            i.odigrajPartiju();
            trenutnoStanje = IGRA_RACUNAR;
            return true;
        }
        return false;
    }

    bool pocniIgruOnline(){
        if((trenutnoStanje == PROFIL_IGRACA || trenutnoStanje == IGRA_RACUNAR) && i.getBrojPartija()+1<=10){
            i.odigrajPartiju();
            trenutnoStanje = IGRA_PROTIVNIK;
            return true;
        }
        return false;
    }

    bool pobedi(){
        if(trenutnoStanje == IGRA_PROTIVNIK && i.getPoeni()+2<10){
            i.dodajPoene(2);
            return true;
        }
        else if(trenutnoStanje == IGRA_RACUNAR && i.getPoeni()+1<10){
            i.dodajPoene(1);
            return true;
        }
        return false;
    }

    bool izgubi(){
        if(trenutnoStanje == IGRA_PROTIVNIK && i.getPoeni()-2>=0){
            i.dodajPoene(-2);
            return true;
        }
        else if(trenutnoStanje == IGRA_RACUNAR && i.getPoeni()-1>=0){
            i.dodajPoene(-1);
            return true;
        }
        return false;
    }

    bool ostvariBonus(){
        if(trenutnoStanje == IGRA_PROTIVNIK && i.getPoeni()>5){
            int bonus = rand()%3+1;
            i.dodajPoene(bonus);
            cout<<"Dobili ste dodatnih "<<bonus<<" poena."<<endl;
            if(i.getPoeni()>10){
                i.setPoeni(10);
            }
            return true;
        }
        return false;
    }

    friend void ispisiIgru(const Igra&); //proglasavanje funkcije za ispis prijateljskom

};

#endif // IGRA_HPP_INCLUDED
