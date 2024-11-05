#ifndef OSOBA_HPP_INCLUDED
#define OSOBA_HPP_INCLUDED

#include "dinstring.hpp"

class Osoba {
protected:
    DinString ime;
    DinString prezime;

public:
    Osoba() : ime(), prezime() {}
    Osoba(const char* s1, const char* s2) : ime(s1), prezime(s2) {}
    Osoba(const DinString& ds1, const DinString& ds2) : ime(ds1), prezime(ds2) {}
    Osoba(const Osoba& o) : ime(o.ime), prezime(o.prezime) {}

    void predstaviSe() const {
        cout << "Ja sam " << ime << " " << prezime << endl;
    }
};

#endif // OSOBA_HPP_INCLUDED