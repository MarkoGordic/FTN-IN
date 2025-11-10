#ifndef IGRA_HPP_INCLUDED
#define IGRA_HPP_INCLUDED

enum StanjeIgre {NEPOZNAT_IGRAC, PROFIL_IGRACA, IGRA_RACUNAR, IGRA_PROTIVNIK};

class Igra {
private:
    Igrac igrac;
    StanjeIgre trenutnoStanje;
public:
    Igra() : igrac() {
        trenutnoStanje = NEPOZNAT_IGRAC;
    }

    Igra(int bp, int p, StanjeIgre si) : igrac(p, bp) {
        trenutnoStanje = si;
    }

    bool prijaviIgraca() {
        if (trenutnoStanje == NEPOZNAT_IGRAC){
            trenutnoStanje = PROFIL_IGRACA;
            return true;
        }
        return false;
    }

    bool odjaviIgraca() {
        if (trenutnoStanje == PROFIL_IGRACA) {
            trenutnoStanje = NEPOZNAT_IGRAC;
            return true;
        }
        return false;
    }

    bool pocniIgruRacunar() {
        if ((trenutnoStanje == PROFIL_IGRACA || trenutnoStanje == IGRA_PROTIVNIK) && igrac.getBrojPartija() + STEP_PARTIJE <= MAX_PARTIJE) {
            igrac.odigrajPartiju();
            trenutnoStanje = IGRA_RACUNAR;
            return true;
        }
        return false;
    }

    bool pocniIgruOnline() {
        if ((trenutnoStanje == PROFIL_IGRACA || trenutnoStanje == IGRA_RACUNAR) && igrac.getBrojPartija() + STEP_PARTIJE <= MAX_PARTIJE) {
            igrac.odigrajPartiju();
            trenutnoStanje = IGRA_PROTIVNIK;
            return true;
        }
        return false;
    }

    bool pobedi() {
        if (trenutnoStanje == IGRA_RACUNAR && igrac.getPoeni() + STEP_POENI_RACUNAR <= MAX_POENI){
            igrac.dodajPoene(STEP_POENI_RACUNAR);
            return true;
        }
        else if (trenutnoStanje == IGRA_PROTIVNIK && igrac.getPoeni() + STEP_POENI_PROTIVNIK <= MAX_POENI){
            igrac.dodajPoene(STEP_POENI_PROTIVNIK);
            return true;
        }
        return false;
    }

    bool izgubi() {
        if (trenutnoStanje == IGRA_RACUNAR && igrac.getPoeni() - STEP_POENI_RACUNAR >= MIN_POENI) {
            igrac.dodajPoene(-STEP_POENI_RACUNAR);
            return true;
        }
        else if (trenutnoStanje == IGRA_PROTIVNIK && igrac.getPoeni() - STEP_POENI_PROTIVNIK >= MIN_POENI){
            igrac.dodajPoene(-STEP_POENI_PROTIVNIK);
            return true;
        }
        return false;
    }

    bool otvoriBonus() {
        if (trenutnoStanje == IGRA_PROTIVNIK && igrac.getPoeni() > 5) {
            int bonus = rand() % 3;
            igrac.dodajPoene(bonus);
            cout << "Dobili ste dodatnih " << bonus <<  " poena." << endl;
            if (igrac.getPoeni() > 10)
                igrac.setPoeni(10);
            return true;
        }
        return false;
    }

    friend void ispisiIgru(const Igra& igra);
};

#endif // IGRA_HPP_INCLUDED
