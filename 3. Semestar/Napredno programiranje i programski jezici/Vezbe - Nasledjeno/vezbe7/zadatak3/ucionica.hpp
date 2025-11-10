#ifndef UCIONICA_HPP_INCLUDED
#define UCIONICA_HPP_INCLUDED

#include "list.hpp"

class Ucionica {
private:
    List <Osoba*> osobe; // 1. *
    DinString naziv;
    int kapacitet;
public:
    Ucionica (const DinString& n, int k) : naziv(n), kapacitet(k) {} // konstruktor za osobe se po defaultu

    bool dodaj (Osoba &o) { // 2. nema const
        if (osobe.size() + 1 > kapacitet) {
            return false;
        }
        return osobe.add(osobe.size() + 1, &o); // 3. &
        // dodajemo na kraj i vracamo uspesnost dodavanja (ili brisanja itd)!!!
    }

    void ispisi () const {
        cout << "Ucionica: " << naziv << endl;
        cout << "Kapacitet: " << kapacitet << endl;
        if (osobe.empty()) {
            cout << "Nema osoba u ucionici!" << endl;
        }
        else {
            cout << "Osobe: " << endl;
            cout << "------------------------" << endl;
            Osoba *pom; // 4. *
            for (int i = 1; i <= osobe.size(); i++) {
                osobe.read(i, pom);
                pom->predstaviSe(); // 5. ->
                // dobijanje krstenog objekta sa Osoba o; o = *pom; o.predstaviSe();
                // ili (*pom).predstaviSe();
            }
            cout << "------------------------" << endl;
        }
    }
};

#endif // UCIONICA_HPP_INCLUDED
