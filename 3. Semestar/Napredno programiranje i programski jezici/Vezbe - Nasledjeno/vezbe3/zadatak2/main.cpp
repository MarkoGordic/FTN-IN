#include <iostream>

using namespace std;

#include "menjac.hpp"
#include "skoljka.hpp"
#include "automobil.hpp"

// on je ispis skoljke u funkciji pa evo i to
void ispisiSkoljku(const Skoljka& s){
    cout << "Boja skoljke: ";
    switch (s.boja){
        case PLAVA:
            cout << "PLAVA";
            break;
        case ZELENA:
            cout << "ZELENA";
            break;
        case CRVENA:
            cout << "CRVENA";
            break;
    }
    cout << endl;
}

void ispisiAuto(const Automobil& a){
    cout << "Broj brzina: " << a.getBrojBrzina() << endl;
    cout << "Tip menjaca: "<<  ((a.getTipMenjaca() == MANUELNI) ? "MANUELNI" : "AUTOMATIK") << endl;
    ispisiSkoljku(a.skoljka);
}

int main()
{
    // menjaci
    Menjac m1, m2(AUTOMATIK, 6), m3(m1);
    cout << "--- menjac m1 ---" << endl;
    m1.setBrojBrzina(4);
    cout << "Broj brzina: " << m1.getBrojBrzina() << endl;
    cout << "Tip menjaca: "<<  ((m1.getTip() == MANUELNI) ? "MANUELNI" : "AUTOMATIK") << endl;
    m1.setBrojBrzina(6);
    m1.setTip(MANUELNI);
    cout << "Broj brzina: " << m1.getBrojBrzina() << endl;
    cout << "Tip menjaca: "<<  ((m1.getTip() == MANUELNI) ? "MANUELNI" : "AUTOMATIK") << endl;

    // skoljke
    Skoljka s1, s2(CRVENA), s3(s1);
    cout << "--- skoljka s1 ---" << endl;
    cout << "Boja skoljke: " << ((s1.getBoja() == PLAVA) ? "PLAVA" : (s1.getBoja() == ZELENA) ? "ZELENA" : "CRVENA") << endl;
    s1.setBoja(CRVENA);
    ispisiSkoljku(s1);
    // cout << "Boja skoljke: " << ((s1.getBoja() == PLAVA) ? "PLAVA" : (s1.getBoja() == ZELENA) ? "ZELENA" : "CRVENA") << endl;

    // automobili
    Automobil a1, a2(5, AUTOMATIK, CRVENA), a3(a2);
    cout << "--- automobil a1 ---" << endl;
    ispisiAuto(a1);
    cout << "--- automobil a2 ---" << endl;
    a2.setBoja(ZELENA);
    a2.setBrojBrzina(6);
    a2.setBrojBrzina(7);
    a2.setTipMenjaca(MANUELNI);
    ispisiAuto(a2);
    cout << "--- automobil a3 ---" << endl;
    ispisiAuto(a3);


    return 0;
}
