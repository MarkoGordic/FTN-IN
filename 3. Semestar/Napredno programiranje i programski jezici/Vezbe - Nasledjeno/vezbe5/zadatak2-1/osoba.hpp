#ifndef OSOBA_HPP_INCLUDED
#define OSOBA_HPP_INCLUDED

class Osoba {
protected:
    DinString ime;
    DinString prezime;
public:
    Osoba() : ime(), prezime() {}

    Osoba (const char* i, const char* p) : ime(i), prezime(p) {}
    Osoba (const DinString& i, const DinString& p) : ime(i), prezime(p) {}
    Osoba (const Osoba& o) : ime(o.ime), prezime(o.prezime) {}
    virtual void predstaviSe () const {
        cout << "Ime: " << ime << endl;
        cout << "Prezime: " << prezime << endl;
    }
};

#endif // OSOBA_HPP_INCLUDED
