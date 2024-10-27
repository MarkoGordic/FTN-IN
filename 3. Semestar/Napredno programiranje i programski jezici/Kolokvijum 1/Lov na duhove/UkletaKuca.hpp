#ifndef UKLETA_KUCA_HPP_INCLUDED
#define UKLETA_KUCA_HPP_INCLUDED

#include <iostream>
#include "Duh.hpp"
#include "Lovac.hpp"

using namespace std;

class UkletaKuca {
private:
    Duh duh1, duh2, duh3;
    Lovac* lovac;

public:
    UkletaKuca() : duh1(), duh2(), duh3(), lovac(nullptr) {}
    UkletaKuca(Duh d1, Duh d2, Duh d3) : duh1(d1), duh2(d2), duh3(d3), lovac(nullptr) {}

    void ulazak(Lovac& lovac) {
        this->lovac = &lovac;
        cout << "Lovac je usao u ukletu kucu!" << endl;
    }

    void izlazak() {
        this->lovac = nullptr;
        cout << "Lovac je napustio ukletu kucu!" << endl;
    }

    void borba() {
        if (!lovac) {
            cout << "Lovac nije usao u kucu!" << endl;
            return;
        }

        if (duh1.getStatus() == AKTIVAN) {
            cout << "Borba sa prvim duhom pocinje!" << endl;
            if (duh1.napadniLovca(*lovac)) {
                duh1.setStatus(UHVACEN);
                lovac->uhvatiDuha();
                cout << "Duh 1 je uhvacen!" << endl;
            } else {
                cout << "Lovac je pretrpeo poraz!" << endl;
                return;
            }
            if (!nastaviBorbu()) return;
        }

        if (duh2.getStatus() == AKTIVAN) {
            cout << "Borba sa drugim duhom pocinje!" << endl;
            if (duh2.napadniLovca(*lovac)) {
                duh2.setStatus(UHVACEN);
                lovac->uhvatiDuha();
                cout << "Duh 2 je uhvacen!" << endl;
            } else {
                cout << "Lovac je pretrpeo poraz!" << endl;
                return;
            }
            if (!nastaviBorbu()) return;
        }

        if (duh3.getStatus() == AKTIVAN) {
            cout << "Borba sa trecim duhom pocinje!" << endl;
            if (duh3.napadniLovca(*lovac)) {
                duh3.setStatus(UHVACEN);
                lovac->uhvatiDuha();
                cout << "Duh 3 je uhvacen!" << endl;
            } else {
                cout << "Lovac je pretrpeo poraz!" << endl;
                return;
            }
        }

        cout << "Borba je zavrsena. Svi duhovi su porazeni." << endl;
    }

    bool nastaviBorbu() {
        char izbor;
        cout << "Da li zelis da nastavis borbu sa sledecim duhom? (d/n): ";
        cin >> izbor;
        if (izbor == 'n' || izbor == 'N') {
            cout << "Lovac je odlucio da odustane!" << endl;
            return false;
        }
        return true;
    }

    void ispisi() const {
        cout << "Duh 1: ";
        duh1.ispisi();
        cout << "Duh 2: ";
        duh2.ispisi();
        cout << "Duh 3: ";
        duh3.ispisi();
    }
};

#endif // UKLETA_KUCA_HPP_INCLUDED
