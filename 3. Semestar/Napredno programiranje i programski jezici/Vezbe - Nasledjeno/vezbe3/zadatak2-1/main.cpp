#include <iostream>

using namespace std;

#include "menjac.hpp"
#include "skoljka.hpp"
#include "automobil.hpp"

void ispisiSkoljku (const Skoljka& s) {
    cout << "Skoljka" << endl;
    cout << "Boja: ";
    switch (s.boja) {
        case ZELENA: cout << "zelena"; break;
        case CRVENA: cout << "crvena"; break;
        case PLAVA: cout << "plava"; break;
    }
    cout << endl << endl;
}

void ispisiMenjac (const Menjac& m) {
    cout << "Menjac" << endl;
    cout << "Vrsta: ";
    switch (m.tip) {
        case AUTOMATIK: cout << "automatik"; break;
        case MANUELNI: cout << "manuelni"; break;
    }
    cout << endl << "Broj brzina: " << m.broj_brzina << endl << endl;
}

void ispisiAuto (const Automobil& a) {
    cout << "---- Automobil ----" << endl;
    ispisiSkoljku(a.skoljka);
    ispisiMenjac(a.menjac);
    cout << "Trenutna brzina: " << a.trenutna_brzina << endl;
    cout << "-------------------" << endl;
}

int main()
{
    Skoljka s1, s2(PLAVA), s3(s1);
    s1.setBoja(ZELENA);
    ispisiSkoljku(s1);

    Menjac m1, m2(AUTOMATIK, 4), m3(m2);
    m1.setBrojBrzina(8);
    m1.setTip(AUTOMATIK);
    ispisiMenjac(m1);

    Automobil a1, a2(7, AUTOMATIK, ZELENA), a3(a1);
    ispisiAuto(a1);

    cout << ((a1.ugasi()) ? "USPESNO" : "NEUSPESNO") << endl;
    cout << ((a1.upali()) ? "USPESNO" : "NEUSPESNO") << endl;
    cout << ((a1.pokvari()) ? "USPESNO" : "NEUSPESNO") << endl;
    cout << ((a1.upali()) ? "USPESNO" : "NEUSPESNO") << endl;
    cout << ((a1.popravi()) ? "USPESNO" : "NEUSPESNO") << endl;
    cout << ((a1.upali()) ? "USPESNO" : "NEUSPESNO") << endl;
    cout << ((a1.povecajBrzinu()) ? "USPESNO" : "NEUSPESNO") << endl;
    cout << ((a1.povecajBrzinu()) ? "USPESNO" : "NEUSPESNO") << endl;
    cout << ((a1.povecajBrzinu()) ? "USPESNO" : "NEUSPESNO") << endl;
    cout << ((a1.smanjiBrzinu()) ? "USPESNO" : "NEUSPESNO") << endl;
    ispisiAuto(a1);

    return 0;
}
