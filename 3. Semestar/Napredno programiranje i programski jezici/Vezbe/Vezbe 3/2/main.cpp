#include <iostream>
using namespace std;

#include "automobil.hpp"

int main(){
    Automobil a;
    a.setBrojBrzina(6);
    a.setTipMenjaca(MANUELNI);
    a.setBoja(CRVENA);

    cout << "Broj brzina: " << a.getBrojBrzina() << endl;
    TipMenjaca tip = a.getTipMenjaca();
    cout << "Tip menjaca: " << (tip == AUTOMATSKI ? "AUTOMATSKI" : "MANUELNI") << endl;
    BojaSkoljke boja = a.getBoja();
    cout << "Boja: " << (boja == PLAVA ? "PLAVA" : (boja == CRVENA ? "CRVENA" : "ZELENA")) << endl;

    return 0;
}