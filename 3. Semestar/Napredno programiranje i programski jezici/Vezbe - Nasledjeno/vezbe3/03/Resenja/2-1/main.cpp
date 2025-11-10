#include <iostream>
#include "automobil.hpp"
using namespace std;

void ispisiMenjac(const Menjac& m){
    cout << "Menjac: " << endl;
    cout << "\tBrzina = " << m.brojBrzina << endl;
    cout << "\tTip = " <<  (m.tip == AUTOMATIK ? "Automatik" : " Manuelni") << endl;
}

void ispisiSkoljku(const Skoljka& s){
    cout << "Skoljka: " << endl;
    cout << "\tBoja = ";

    switch(s.boja){
    case PLAVA:
            cout << "Plava";
            break;
    case ZELENA:
            cout << "Zelena";
            break;
    case CRVENA:
            cout << "Crvena";
            break;
    }
    cout << endl;
}

void ispisiAutomobil(const Automobil& a){
    cout << "Automobil" << endl;
    cout << "*******************" << endl;
    ispisiMenjac(a.menjac);
    ispisiSkoljku(a.skoljka);

    cout << "Stanje: ";
    switch(a.stanje) {
    case UGASEN:
        cout << "ugasen";
        break;
    case U_VOZNJI:
        cout << "u voznji";
        break;
    case POKVAREN:
        cout << "pokvaren";
        break;
    }
    cout << endl;

    cout << "Trenutna brzina: " << a.trenutnaBrzina << endl;
    cout << endl << endl;
}


int main()
{
    Menjac m1, m2(MANUELNI, 5), m3(m1);
    ispisiMenjac(m1);
    ispisiMenjac(m2);
    ispisiMenjac(m3);

    cout << endl;

    Skoljka s1, s2(CRVENA), s3(s2);
    ispisiSkoljku(s1);
    ispisiSkoljku(s2);
    ispisiSkoljku(s3);

    cout << endl;

    Automobil a1, a2(AUTOMATIK, 3, CRVENA, U_VOZNJI, 2), a3(a2);
    ispisiAutomobil(a1);
    ispisiAutomobil(a2);
    ispisiAutomobil(a3);


    // Testiramo a2. Ako se u zadatku ne trazi funkcija meni() dovoljno je pozvati svaki metod bar jednom

    cout << "*************" << endl;
    if (a2.upali())
        cout << "OK";
    else
        cout << "greska";
    cout << endl ;
    ispisiAutomobil(a2);
    cout << endl << endl;

    cout << "*************" << endl;
    if (a2.ugasi())
        cout << "OK";
    else
        cout << "greska";
    cout << endl ;
    ispisiAutomobil(a2);
    cout << endl << endl;


    cout << "*************" << endl;
    a2.upali();
    a2.povecajBrzinu();
    a2.povecajBrzinu();
    a2.smanjiBrzinu();

    cout << endl ;
    ispisiAutomobil(a2);
    cout << endl << endl;

    // probamo da smanjimo ispod 0
    a2.smanjiBrzinu();
    if (a2.smanjiBrzinu())
        cout << "OK";
    else
        cout << "greska";
    cout << endl ;
    ispisiAutomobil(a2);
    cout << endl << endl;

    // probamo da povecamo iznad max (3)
    a2.povecajBrzinu();
    a2.povecajBrzinu();
    a2.povecajBrzinu();
    a2.povecajBrzinu();

    ispisiAutomobil(a2);
    cout << endl << endl;

    // probamo da popravimo ispravan
    if (a2.popravi())
        cout << "OK";
    else
        cout << "greska";
    cout << endl ;
    ispisiAutomobil(a2);
    cout << endl << endl;

    a2.pokvari();
    ispisiAutomobil(a2);

    a2.popravi();
    ispisiAutomobil(a2);

    return 0;
}
