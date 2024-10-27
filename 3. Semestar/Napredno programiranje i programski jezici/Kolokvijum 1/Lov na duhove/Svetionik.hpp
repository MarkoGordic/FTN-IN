#ifndef SVETIONIK_HPP_INCLUDED
#define SVETIONIK_HPP_INCLUDED

#include <iostream>
#include "Duh.hpp"
#include "Lovac.hpp"

using namespace std;

class Svetionik {
private:
    Duh duh;
    Lovac* lovac;

public:
    Svetionik() : duh(), lovac(nullptr) {}
    Svetionik(Duh duh) : duh(duh), lovac(nullptr) {}

    void ulazak(Lovac& lovac) {
        this->lovac = &lovac;
    }

    void izlazak() {
        this->lovac = nullptr;
    }

    bool duel() {
        if (!lovac) {
            cout << "Lovac nije ušao u svetionik!\n";
            return false;
        }

        cout << "Borba izmedju lovca i duha pocinje!\n";
        
        if (duh.napadniLovca(*lovac)) {
            duh.setStatus(UHVACEN);
            lovac->uhvatiDuha();
            cout << "Duh je uhvacen!\n";
            return true;
        } else {
            cout << "Lovac je pretrpeo poraz!\n";
            return false;
        }
    }

    void ispisi() const {
        cout << "Informacije o duhu u svetioniku:\n";
        duh.ispisi();
    }
};

#endif // SVETIONIK_HPP_INCLUDED
