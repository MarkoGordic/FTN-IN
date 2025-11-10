#ifndef VOCE_HPP_INCLUDED
#define VOCE_HPP_INCLUDED

#include "proizvod.hpp"

class Voce : public Proizvod {
private:
    DinString zemljaPorekla;
    int rokTrajanja; // u danima
public:
    Voce(const DinString& n, const DinString& zp, int rt, int c) : Proizvod(n, c), zemljaPorekla(zp), rokTrajanja(rt){}

    void ispisi(){
        Proizvod::ispisi();
        cout << "Zemlja porekla: " << zemljaPorekla << endl;
        cout << "Rok trajanja: " << rokTrajanja << endl;
    }

    void izracunajPopust(){
        double popust = 0.33;
        if (rokTrajanja > 0 && rokTrajanja < 5){
            popust = 0.66;
        } else if (rokTrajanja <= 0){
            popust = 1;
        }

        cena -= cena * popust;
    }
};


#endif // VOCE_HPP_INCLUDED

