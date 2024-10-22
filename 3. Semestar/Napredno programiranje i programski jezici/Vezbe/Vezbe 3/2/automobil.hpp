#include "menjac.hpp"
#include "skoljka.hpp"

class Automobil {
private:
    Menjac menjac;
    Skoljka skoljka;

public:
    Automobil(){
        menjac = Menjac();
        skoljka = Skoljka();
    };

    Automobil(Menjac m, Skoljka s): menjac(m), skoljka(s){};

    Automobil(const Automobil& a){
        menjac = a.menjac;
        skoljka = a.skoljka;
    };

    bool setBrojBrzina(int b){
        return menjac.setBrojBrzina(b);
    }

    void setBoja(BojaSkoljke b){
        skoljka.setBoja(b);
    }

    void setTipMenjaca(TipMenjaca t){
        menjac.setTip(t);
    }

    int getBrojBrzina()const{
        return menjac.getBrojBrzina();
    }

    TipMenjaca getTipMenjaca()const{
        return menjac.getTip();
    }

    BojaSkoljke getBoja()const{
        return skoljka.getBoja();
    }
};