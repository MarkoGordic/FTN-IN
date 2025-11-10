#ifndef AUTOMOBIL_HPP_INCLUDED
#define AUTOMOBIL_HPP_INCLUDED

enum Stanje {UGASEN, UVOZNJI, POKVAREN};

class Automobil{
private:
    Skoljka skoljka;
    Menjac menjac;
    Stanje stanje;
    int trenutna_brzina;
public:
    Automobil () : skoljka(), menjac() {
        stanje = UGASEN;
        trenutna_brzina = 0;
    }
    Automobil (int bb, TipMenjaca t, BojaSkoljke bs) : skoljka(bs), menjac(t, bb) {
        stanje = UGASEN;
        trenutna_brzina = 0;
    }
    Automobil (const Automobil& a) : skoljka(a.skoljka), menjac(a.menjac) {
        stanje = a.stanje;
        trenutna_brzina = a.trenutna_brzina;
    }

    bool upali(){
        if (stanje == UGASEN){
            stanje = UVOZNJI;
            return true;
        }
        return false;
    }
    bool ugasi() {
        if (stanje == UVOZNJI){
            stanje = UGASEN;
            trenutna_brzina = 0;
            return true;
        }
        return false;
    }
    bool pokvari() {
        if (stanje != POKVAREN){
            stanje = POKVAREN;
            trenutna_brzina = 0;
            return true;
        }
        return false;
    }
    bool popravi() {
        if (stanje == POKVAREN){
            stanje = UGASEN;
            trenutna_brzina = 0;
            return true;
        }
        return false;
    }
    bool povecajBrzinu() {
        if (stanje == UVOZNJI && trenutna_brzina + 1 <= menjac.getBrojBrzina()){
            trenutna_brzina++;
            return true;
        }
        return false;
    }
    bool smanjiBrzinu() {
        if (stanje == UVOZNJI && trenutna_brzina - 1 >= 0){
            trenutna_brzina--;
            return true;
        }
        return false;
    }

    friend void ispisiAuto (const Automobil& a);
};

#endif // AUTOMOBIL_HPP_INCLUDED
