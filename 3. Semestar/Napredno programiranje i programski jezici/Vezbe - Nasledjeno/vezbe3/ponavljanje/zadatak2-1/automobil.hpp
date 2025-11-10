#ifndef AUTOMOBIL_HPP_INCLUDED
#define AUTOMOBIL_HPP_INCLUDED

enum TrenutnoStanje {UGASEN, UVOZNJI, POKVAREN};

class Automobil {
private:
    Menjac menjac;
    Skoljka skoljka;
    TrenutnoStanje stanje;
    int trenutnaBrzina;
public:
    Automobil () : menjac(), skoljka() {
        stanje = UGASEN;
        trenutnaBrzina = 0;
    }

    Automobil (int bb, TipMenjaca tm, Boja b, TrenutnoStanje ts, int tb) : menjac(bb, tm), skoljka(b) {
        stanje = ts;
        trenutnaBrzina = tb;
    }

    Automobil (const Automobil& a) : menjac(a.menjac), skoljka(a.skoljka) {
        stanje = a.stanje;
        trenutnaBrzina = a.trenutnaBrzina;
    }

    bool upali () {
        if (stanje == UGASEN) {
            stanje = UVOZNJI;
            return true;
        }
        return false;
    }

    bool ugasi () {
        if (stanje == UVOZNJI) {
            stanje = UGASEN;
            trenutnaBrzina = 0;
            return true;
        }
        return false;
    }

    bool pokvari () {
        if (stanje != POKVAREN) {
            stanje = POKVAREN;
            trenutnaBrzina = 0;
            return true;
        }
        return false;
    }

    bool popravi () {
        if (stanje == POKVAREN) {
            stanje = UGASEN;
            trenutnaBrzina = 0;
            return true;
        }
        return false;
    }

    bool povecajBrzinu () {
        if (stanje == UVOZNJI && trenutnaBrzina < menjac.getBrojBrzina()) {
            trenutnaBrzina++;
            return true;
        }
        return false;
    }

    bool smanjiBrzinu () {
        if (stanje == UVOZNJI && trenutnaBrzina > 0) {
            trenutnaBrzina--;
            return true;
        }
        return false;
    }

    friend void ispisAutomobil (const Automobil& a);
};

#endif // AUTOMOBIL_HPP_INCLUDED
