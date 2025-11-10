#ifndef MENJAC_HPP_INCLUDED
#define MENJAC_HPP_INCLUDED

enum TipMenjaca {AUTOMATIK, MANUELNI};

class Menjac{
private:
    int broj_brzina;
    TipMenjaca tip;
public:
    Menjac(){
        tip = AUTOMATIK;
        broj_brzina = 5;
    }
    Menjac(TipMenjaca tm, int bb){
        tip = tm;
        broj_brzina = bb;
    }
    Menjac(const Menjac& m){
        broj_brzina = m.tip;
        broj_brzina = m.broj_brzina;
    }
    bool setBrojBrzina(int bb){
        if (bb == 5 || bb == 6){
            broj_brzina = bb;
            return true;
        }
        else {
            return false;
        }
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
};

#endif // MENJAC_HPP_INCLUDED
