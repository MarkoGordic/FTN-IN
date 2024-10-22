#ifndef MENJAC_HPP_INCLUDED
#define MENJAC_HPP_INCLUDED

enum TipMenjaca {AUTOMATSKI, MANUELNI};

class Menjac {
private:
    int brzina;
    TipMenjaca tip;

public:
    Menjac(){
        brzina = 3;
        tip = MANUELNI;
    };

    Menjac(int b, TipMenjaca t){
        brzina = b;
        tip = t;
    };

    Menjac(const Menjac& m){
        brzina = m.brzina;
        tip = m.tip;
    };

    bool setBrojBrzina(int b){
        if(b != 5 && b != 6){
            brzina = b;
            return true;
        }

        return false;
    }

    void setTipMenjaca(TipMenjaca t){
        tip = t;
    }

    int getBrojBrzina()const{
        return brzina;
    }

    TipMenjaca getTipMenjaca()const{
        return tip;
    }

};

#endif // MENJAC_HPP_INCLUDED