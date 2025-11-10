#include <iostream>

using namespace std;

#include "menjac.hpp"
#include "skoljka.hpp"
#include "automobil.hpp"

void ispisMenjac (const Menjac& m) {
    cout << "---- Menjac ----" << endl;
    cout << "Tip: " << ((m.tip == AUTOMATIK) ? "AUTOMATIK" : "MANUELNI") << endl;
    cout << "Broj brzina: " << m.brojBrzina << endl;
    cout << "----------------" << endl << endl;
}

void ispisSkoljka (const Skoljka& s) {
    cout << "---- Skoljka ----" << endl;
    cout << "Boja: ";
    switch (s.boja) {
        case ZELENA: cout << "ZELENA" << endl; break;
        case CRVENA: cout << "CRVENA" << endl; break;
        case PLAVA: cout << "PLAVA" << endl; break;
    }
    cout << "-----------------" << endl << endl;
}

void ispisAutomobil (const Automobil& a) {
    cout << "---- Automobil ----" << endl;
    ispisMenjac(a.menjac);
    ispisSkoljka(a.skoljka);


    cout << "Stanje: ";
    switch (a.stanje) {
        case UGASEN: cout << "UGASEN" << endl; break;
        case UVOZNJI: cout << "U VOZNJI" << endl; break;
        case POKVAREN: cout << "POKVAREN" << endl; break;
    }
    cout << "Trenutna brzina: " << a.trenutnaBrzina << endl;
    cout << "-------------------" << endl << endl;
}

int meni () {
    int n;
    cout << "Opcija 1: Upali" << endl;
    cout << "Opcija 2: Ugasi" << endl;
    cout << "Opcija 3: Pokvari" << endl;
    cout << "Opcija 4: Popravi" << endl;
    cout << "Opcija 5: Povecaj brzinu" << endl;
    cout << "Opcija 6: Smanji brzinu" << endl;
    cout << "Opcija 0: Izlaz" << endl;
    cout << "Opcija: ";
    cin >> n;
    return n;
}

void ispisUspeha (bool uspeh) {
    cout << ((uspeh) ? "USPESNO" : "NEUSPESNO") << endl;
}

int main()
{
    Menjac m1, m2(5, AUTOMATIK), m3(m1);
    ispisMenjac(m1);

    m1.setBrojBrzina(6);
    m1.setTipMenjaca(AUTOMATIK);

    ispisMenjac(m1);

    cout << "MENJAC M3" << endl;
    cout << "Tip: " << ((m3.getTipMenjaca() == AUTOMATIK) ? "AUTOMATIK" : "MANUELNI") << endl;
    cout << "Broj brzina: " << m3.getBrojBrzina() << endl << endl;

    Skoljka s1, s2(CRVENA), s3(s1);
    ispisSkoljka(s1);

    s1.setBoja(CRVENA);

    ispisSkoljka(s1);

    cout << "SKOLJKA S3" << endl;
    cout << "Boja: ";
    switch (s3.getBoja()) {
        case ZELENA: cout << "ZELENA" << endl; break;
        case CRVENA: cout << "CRVENA" << endl; break;
        case PLAVA: cout << "PLAVA" << endl; break;
    }
    cout << endl;

    Automobil a1, a2(4, AUTOMATIK, CRVENA, UGASEN, 0), a3(a1);

    int opcija = 0;
    do {
        ispisAutomobil (a1);
        opcija = meni();
        switch (opcija) {
            case 1: ispisUspeha(a1.upali()); break;
            case 2: ispisUspeha(a1.ugasi()); break;
            case 3: ispisUspeha(a1.pokvari()); break;
            case 4: ispisUspeha(a1.popravi()); break;
            case 5: ispisUspeha(a1.povecajBrzinu()); break;
            case 6: ispisUspeha(a1.smanjiBrzinu()); break;
            case 0: cout << "Pozdrav!" << endl; break;
            default: cout << "Nepoznata opcija!" << endl;
        }
    } while (opcija != 0);
    return 0;
}
