#ifndef OSOBA_HPP_INCLUDED
#define OSOBA_HPP_INCLUDED

class Osoba {
protected:
    DinString ime, prezime;
public:
    Osoba() : ime("Nenad"), prezime("Lukic") {}

    Osoba(const DinString& i, const DinString& p) : ime(i), prezime(p) {}

    Osoba(const Osoba& o) : ime(o.ime), prezime(o.prezime) {}

    virtual void ispis() const {
        cout << "Zovem se " << ime << " " << prezime << "." << endl;
    }
};

#endif // OSOBA_HPP_INCLUDED
