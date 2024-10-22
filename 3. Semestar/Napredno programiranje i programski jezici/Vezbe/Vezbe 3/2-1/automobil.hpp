#include "menjac.hpp"
#include "skoljka.hpp"

enum StanjeAutomobila {
    UGAŠEN,
    U_VOŽNJI,
    POKVAREN
};

class Automobil {
private:
    Menjac menjac;
    Skoljka skoljka;
    StanjeAutomobila stanje;
    int trenutnaBrzina;

public:
    Automobil(): menjac(), skoljka(){
        stanje = UGAŠEN;
        trenutnaBrzina = 0;
    }

    Automobil(Menjac m, Skoljka s): menjac(m), skoljka(s){
        stanje = UGAŠEN;
        trenutnaBrzina = 0;
    }

    Automobil(const Automobil& a): menjac(a.menjac), skoljka(a.skoljka){
        stanje = a.stanje;
        trenutnaBrzina = a.trenutnaBrzina;
    }

    bool upali(){
        if(stanje == UGAŠEN){
            stanje = U_VOŽNJI;
            return true;
        }

        return false;
    }

    bool ugasi(){
        if(stanje == U_VOŽNJI){
            stanje = UGAŠEN;
            trenutnaBrzina = 0;
            return true;
        }

        return false;
    }

    bool pokvari(){
        if(stanje != POKVAREN){
            stanje = POKVAREN;
            trenutnaBrzina = 0;
            return true;
        }
        return false;
    }

    bool popravi(){
        if(stanje == POKVAREN){
            stanje = UGAŠEN;
            trenutnaBrzina = 0;
            return true;
        }
        return false;
    }

    bool povecajBrzinu(){
        if(stanje == U_VOŽNJI && trenutnaBrzina < menjac.getBrojBrzina()){
            trenutnaBrzina++;
            return true;
        }
        return false;
    }

    bool smanjiBrzinu(){
        if(stanje == U_VOŽNJI && trenutnaBrzina > 0){
            trenutnaBrzina--;
            return true;
        }
        return false;
    }

    int getBrojBrzina()const{
        return menjac.getBrojBrzina();
    }

    TipMenjaca getTipMenjaca()const{
        return menjac.getTipMenjaca();
    }

    BojaSkoljke getBoja()const{
        return skoljka.getBoja();
    }

    StanjeAutomobila getStanje()const{
        return stanje;
    }

    int getTrenutnaBrzina()const{
        return trenutnaBrzina;
    }

    void toString()const{
        cout << "Broj brzina: " << menjac.getBrojBrzina() << endl;
        cout << "Tip menjaca: " << (menjac.getTipMenjaca() == AUTOMATSKI ? "AUTOMATSKI" : "MANUELNI") << endl;
        cout << "Boja: " << (skoljka.getBoja() == PLAVA ? "PLAVA" : (skoljka.getBoja() == CRVENA ? "CRVENA" : "ZELENA")) << endl;
        cout << "Stanje: " << (stanje == UGAŠEN ? "UGAŠEN" : (stanje == U_VOŽNJI ? "U VOŽNJI" : "POKVAREN")) << endl;
        cout << "Trenutna brzina: " << trenutnaBrzina << endl;
    }
};