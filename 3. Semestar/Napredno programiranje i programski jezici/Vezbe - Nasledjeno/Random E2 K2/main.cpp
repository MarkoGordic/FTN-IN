#include <iostream>

using namespace std;

#include "dinstring.hpp"
#include "list.hpp"
#include "regrut.hpp"
#include "strelac.hpp"
#include "macevalac.hpp"
#include "ceta.hpp"

int main()
{
    Strelac s1("djole", "mjau", 2.1, begginer, 1500, pracka), s2("SMEKER", "mjau", 5.1, begginer, 1800, luk), s3("macan", "mjau", 1.1, begginer, 2500, samostrel);
    s1.predstaviSe();
    s2.predstaviSe();
    s3.predstaviSe();

    s1.unaprediOruzje(300);
    s2.unaprediOruzje(400);
    s3.unaprediOruzje(500);

    s1.predstaviSe();
    s2.predstaviSe();
    s3.predstaviSe();

    cout << s1.getImePrezime() << endl;
    cout << s1.getGodineSluzbe() << endl << endl << endl;


    Macevalac m1("jak", "momak", 5.6, experienced, 2000, true);

    m1.predstaviSe();
    cout << m1.getImePrezime() << endl;
    cout << m1.getGodineSluzbe() << endl;
    cout << m1 << endl << endl << endl;

    Ceta c1("mala druzina", "velika pingvin kradja", 3);
    c1.dodajRegruta(s1);
    c1.dodajRegruta(s1);
    c1.dodajRegruta(s2);
    c1.dodajRegruta(s3);
    c1.dodajRegruta(m1);
    c1.ispisi();

    cout << (c1.postojiRegrut(s1) ? "da s1" : "ne s1") << endl;
    cout << (c1.postojiRegrut(m1) ? "da m1" : "ne m1") << endl;

    c1.izbaciRegruta(s1);
    c1.izbaciRegruta(m1);
    c1.ispisi();
    return 0;
}
