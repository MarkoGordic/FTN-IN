#ifndef AUTOMOBIL_HPP_INCLUDED
#define AUTOMOBIL_HPP_INCLUDED

#include "menjac.hpp"
#include "skoljka.hpp"

enum StanjeAutomobila {UGASEN, U_VOZNJI, POKVAREN};

class Automobil {

private:
    Menjac menjac;
    Skoljka skoljka;
    StanjeAutomobila stanje;
    int trenutnaBrzina;

public:
    Automobil() : menjac(), skoljka(), stanje(UGASEN), trenutnaBrzina(0){}
    Automobil(TipMenjaca tip, int brojBrzina, BojaSkoljke boja, StanjeAutomobila s, int b)
    : menjac(tip, brojBrzina), skoljka(boja), stanje(s), trenutnaBrzina(b) {}
    Automobil(const Automobil& a) :
        menjac(a.menjac), skoljka(a.skoljka), stanje(a.stanje), trenutnaBrzina(a.trenutnaBrzina) {}

    bool upali() {
        if (stanje != UGASEN)
            return false;

        stanje = U_VOZNJI;
        return true;
    }

    bool ugasi() {
        if (stanje != U_VOZNJI)
            return false;

        stanje = UGASEN;
        trenutnaBrzina = 0;
        return true;
    }

    bool pokvari() {
        if (stanje == POKVAREN)
            return false;

        stanje = POKVAREN;
        trenutnaBrzina = 0;
        return true;
    }

    bool popravi() {
        if (stanje != POKVAREN)
            return false;

        stanje = UGASEN;
        trenutnaBrzina = 0;
        return true;
    }

    bool povecajBrzinu() {
        if ((stanje != U_VOZNJI) || (trenutnaBrzina == menjac.getBrojBrzina()))
            return false;

        trenutnaBrzina++;
        return true;
    }

    bool smanjiBrzinu() {
        if ((stanje != U_VOZNJI) || (trenutnaBrzina == 0))
            return false;

        trenutnaBrzina--;
        return true;
    }


    friend void ispisiAutomobil(const Automobil&);

};

#endif // AUTOMOBIL_HPP_INCLUDED
