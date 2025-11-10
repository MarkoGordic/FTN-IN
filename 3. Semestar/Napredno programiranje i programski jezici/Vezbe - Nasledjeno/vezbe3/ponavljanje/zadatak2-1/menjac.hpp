#ifndef MENJAC_HPP_INCLUDED
#define MENJAC_HPP_INCLUDED

enum TipMenjaca {AUTOMATIK, MANUELNI};

class Menjac {
private:
    int brojBrzina;
    TipMenjaca tip;
public:
    Menjac () {
        brojBrzina = 3;
        tip = MANUELNI;
    }

    Menjac (int bb, TipMenjaca tm) {
        brojBrzina = bb;
        tip = tm;
    }

    Menjac (const Menjac& m) {
        brojBrzina = m.brojBrzina;
        tip = m.tip;
    }

    void setBrojBrzina (int bb) {
        brojBrzina = bb;
    }

    void setTipMenjaca (TipMenjaca tm) {
        tip = tm;
    }

    int getBrojBrzina () const {
        return brojBrzina;
    }

    TipMenjaca getTipMenjaca () const {
        return tip;
    }

    friend void ispisMenjac (const Menjac& m);
};

#endif // MENJAC_HPP_INCLUDED
