#ifndef ODECA_HPP_INCLUDED
#define ODECA_HPP_INCLUDED

#include "proizvod.hpp"

enum Velicina {XS, S, M, L, XL};
enum Tip { MAJICA, PANTALONE};

class Odeca : public Proizvod {
private:
    static int brojVelikeOdece;
    Velicina v;
    Tip t;
public:
    Odeca(Velicina vv, Tip tt, int c, const DinString& ds) : Proizvod(ds,c), v(vv), t(tt) {
        if (vv == L || vv == XL){
            brojVelikeOdece++;
        }
    }

    ~Odeca(){
        if (v == L || v == XL){
            brojVelikeOdece--;
        }
    }

    void izracunajPopust(){

        double popust = 0;
        if (t == MAJICA){
            if (v == XS){
                popust = 0.6;
            } else {
                popust = 0.5;
            }
        } else {
            popust = 0.33;
        }

        cena -= cena * popust;
    }

    void ispisi(){
        Proizvod::ispisi();
        cout << "Velicina: ";

        switch(v){
            case XS: cout << "XS" << endl; break;
            case S: cout << "S" << endl; break;
            case M: cout << "M" << endl; break;
            case L: cout << "L" << endl; break;
            case XL: cout << "XL" << endl; break;
        }

        cout << "Tip: ";
        switch (t){
            case MAJICA: cout << "Majica" << endl; break;
            case PANTALONE: cout << "Pantalone" << endl; break;
        }
    }

    int getBrojVelikeOdece() const { return brojVelikeOdece; }

};


#endif // ODECA_HPP_INCLUDED

