#ifndef UCIONICA_HPP_INCLUDED
#define UCIONICA_HPP_INCLUDED

#include "list.hpp"

template <int KAPACITET>
class Ucionica {
private:
    List <Osoba> osobe;
    DinString naziv;
public:
    Ucionica (const DinString& n) : naziv(n) {} // konstruktor za osobe se po defaultu

    bool dodaj (const Osoba &o) {
        if (osobe.size() + 1 > KAPACITET) {
            return false;
        }
        return osobe.add(osobe.size() + 1, o); // dodajemo na kraj i vracamo uspesnost dodavanja (ili brisanja itd)!!!
    }

    void ispisi () const {
        cout << "Ucionica: " << naziv << endl;
        cout << "Kapacitet: " << KAPACITET << endl;
        if (osobe.empty()) {
            cout << "Nema osoba u ucionici!" << endl;
        }
        else {
            cout << "Osobe: " << endl;
            cout << "------------------------" << endl;
            Osoba pom;
            for (int i = 1; i <= osobe.size(); i++) {
                osobe.read(i, pom);
                pom.predstaviSe();
            }
            cout << "------------------------" << endl;
        }
    }
};

#endif // UCIONICA_HPP_INCLUDED
