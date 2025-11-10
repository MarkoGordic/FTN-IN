#ifndef IGRA_HPP_INCLUDED
#define IGRA_HPP_INCLUDED

enum StanjeIgre {NEPOZNAT_IGRAC, PROFIL_IGRACA, IGRA_RACUNAR, IGRA_PROTIVNIK};

class Igra {
private:
    Igrac igrac;
    StanjeIgre trenutnoStanje;
public:
    Igra () : igrac(), trenutnoStanje(NEPOZNAT_IGRAC) {}

    Igra (int p, int bp, StanjeIgre si) : igrac(p, bp), trenutnoStanje(si) {}

    bool prijaviIgraca () {
        if (trenutnoStanje == NEPOZNAT_IGRAC){
            trenutnoStanje = PROFIL_IGRACA;
            return true;
        }
        return false;
    }

    bool odjaviIgraca () {
        if (trenutnoStanje == PROFIL_IGRACA){
            trenutnoStanje = NEPOZNAT_IGRAC;
            igrac.resetuj();
            return true;
        }
        return false;
    }

    bool pocniIgruRacunar () {
        if ((trenutnoStanje == PROFIL_IGRACA || trenutnoStanje == IGRA_PROTIVNIK) && igrac.getBrojPartija() + 1 <= 10){
            trenutnoStanje = IGRA_RACUNAR;
            igrac.odigrajPartiju();
            return true;
        }
        return false;
    }

    bool pocniIgruOnline () {
        if ((trenutnoStanje == PROFIL_IGRACA || trenutnoStanje == IGRA_RACUNAR) && igrac.getBrojPartija() + 1 <= 10){
            trenutnoStanje = IGRA_PROTIVNIK;
            igrac.odigrajPartiju();
            return true;
        }
        return false;
    }

    bool pobedi () {
        if (trenutnoStanje == IGRA_RACUNAR && igrac.getPoeni() + 1 <= 10){
            igrac.dodajPoene(1);
            return true;
        }
        else if (trenutnoStanje == IGRA_PROTIVNIK && igrac.getPoeni() + 2 <= 10){
            igrac.dodajPoene(2);
            return true;
        }
        return false;
    }

    bool izgubi () {
        if (trenutnoStanje == IGRA_RACUNAR && igrac.getPoeni() - 1 >= 0){
            igrac.dodajPoene(-1);
            return true;
        }
        else if (trenutnoStanje == IGRA_PROTIVNIK && igrac.getPoeni() - 2 >= 0){
            igrac.dodajPoene(-2);
            return true;
        }
        return false;
    }

    bool otvoriBonus () {
        if (trenutnoStanje == IGRA_PROTIVNIK && igrac.getPoeni() > 5){
            int bonus = rand() % 3;
            igrac.dodajPoene(bonus);
            cout << "Dobili ste dodatnih " << bonus << " poena." << endl;
            if (igrac.getPoeni() > 10){
                igrac.setPoeni(10);
            }
            return true;
        }
        return false;
    }

    friend void ispisiIgru(const Igra& igra);
};

#endif // IGRA_HPP_INCLUDED
