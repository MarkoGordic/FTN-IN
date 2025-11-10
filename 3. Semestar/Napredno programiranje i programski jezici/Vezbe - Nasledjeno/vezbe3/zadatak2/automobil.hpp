#ifndef AUTOMOBIL_HPP_INCLUDED
#define AUTOMOBIL_HPP_INCLUDED

class Automobil {
private:
    Skoljka skoljka;
    Menjac menjac;
public:
    Automobil() : skoljka(), menjac() {}
    Automobil(int bb, TipMenjaca t, BojaSkoljke b) : skoljka(b), menjac(t, bb) {}
    Automobil(const Automobil& a) : skoljka(a.skoljka), menjac(a.menjac) {}

    bool setBrojBrzina(int brb){
        return menjac.setBrojBrzina(brb);
    }
    void setBoja(BojaSkoljke b) {
        skoljka.setBoja(b);
    }
    void setTipMenjaca(TipMenjaca tm) {
        menjac.setTip(tm);
    }
    int getBrojBrzina() const {
        return menjac.getBrojBrzina();
    }
    TipMenjaca getTipMenjaca () const {
        return menjac.getTip();
    }
    BojaSkoljke getBoja() const {
        return skoljka.getBoja();
    }

    friend void ispisiAuto(const Automobil& a);
};

#endif // AUTOMOBIL_HPP_INCLUDED
