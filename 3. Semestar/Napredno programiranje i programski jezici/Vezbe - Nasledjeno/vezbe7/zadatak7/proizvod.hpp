#ifndef PROIZVOD_HPP_INCLUDED
#define PROIZVOD_HPP_INCLUDED

class Proizvod {
protected:
    int cena;
    DinString naziv;
public:
    Proizvod (int c, const DinString& ime) : cena(c), naziv(ime) {}

    Proizvod (int c, const char* ime) : cena(c), naziv(ime) {}

    virtual void ispisi () {
        cout << "Proizvod: " << naziv << endl;
        cout << "Cena: " << cena << endl;
    }

    DinString getNaziv() const {
        return naziv;
    }

    int getCena () const {
        return cena;
    }

    virtual void izracunajPopust () = 0;
};

#endif // PROIZVOD_HPP_INCLUDED
