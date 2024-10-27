#ifndef LOVNADUHOVE_HPP_INCLUDED
#define LOVNADUHOVE_HPP_INCLUDED

#include <iostream>
#include "Lovac.hpp"
#include "UkletaKuca.hpp"
#include "Svetionik.hpp"

using namespace std;

class LovNaDuhove {
private:
    Lovac lovac;
    UkletaKuca ukletaKuca;
    Svetionik svetionik;

public:
    LovNaDuhove(Lovac lovac, UkletaKuca ukletaKuca, Svetionik svetionik)
        : lovac(lovac), ukletaKuca(ukletaKuca), svetionik(svetionik) {}

    void zapocniLov() {
        char izbor;
        cout << "Gde zelis da zapocnes lov? (k - Ukleta Kuca, s - Svetionik): ";
        cin >> izbor;

        if (izbor == 'k' || izbor == 'K') {
            cout << "Lovac ulazi u ukletu kucu!\n";
            ukletaKuca.ulazak(lovac);
            ukletaKuca.borba();
            cout << "Lovac izlazi iz uklete kuce.\n";
            ukletaKuca.izlazak();
        } else if (izbor == 's' || izbor == 'S') {
            cout << "Lovac ulazi u svetionik!\n";
            svetionik.ulazak(lovac);
            svetionik.duel();
            cout << "Lovac izlazi iz svetionika.\n";
            svetionik.izlazak();
        } else {
            cout << "Nevalidan izbor!\n";
        }
    }

    void ispisi() {
        cout << "Trenutna situacija:\n";
        cout << "Lovac:\n";
        lovac.ispisi();

        cout << "\nUkleta kuca:\n";
        ukletaKuca.ispisi();

        cout << "\nSvetionik:\n";
        svetionik.ispisi();
    }
};

#endif // LOVNADUHOVE_HPP_INCLUDED
