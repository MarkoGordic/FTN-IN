#ifndef OSOBA_HPP_INCLUDED
#define OSOBA_HPP_INCLUDED

class Osoba {
protected:
    DinString ime, prezime;

public:
    Osoba () {} // mozemo i Osoba () : ime(), prezime() {}, ali to se po defaultu radi
    Osoba (const DinString &i, const DinString &p) : ime(i), prezime(p) {}
    Osoba (const Osoba &o) : ime(o.ime), prezime(o.prezime) {}

    virtual void predstaviSe () const {
        if (ime == "" && prezime == "")
            cout << "X" << endl;
        else
            cout << "Ja sam " << ime << " " << prezime << "." << endl;
    }
};


#endif // OSOBA_HPP_INCLUDED
