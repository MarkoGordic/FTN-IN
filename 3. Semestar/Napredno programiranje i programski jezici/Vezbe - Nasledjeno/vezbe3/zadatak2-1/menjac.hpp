#ifndef MENJAC_HPP_INCLUDED
#define MENJAC_HPP_INCLUDED

enum TipMenjaca {AUTOMATIK, MANUELNI};

class Menjac{
private:
    int broj_brzina;
    TipMenjaca tip;
public:
    Menjac(){
        tip = MANUELNI;
        broj_brzina = 3;
    }
    Menjac(TipMenjaca tm, int bb){
        tip = tm;
        broj_brzina = bb;
    }
    Menjac(const Menjac& m){
        broj_brzina = m.tip;
        broj_brzina = m.broj_brzina;
    }
    void setBrojBrzina(int bb){
        broj_brzina = bb;
    }
    void setTip(TipMenjaca tm) {
        tip = tm;
    }
    int getBrojBrzina() const {
        return broj_brzina;
    }
    TipMenjaca getTip() const {
        return tip;
    }

    friend void ispisiMenjac (const Menjac& m);
};

#endif // MENJAC_HPP_INCLUDED
