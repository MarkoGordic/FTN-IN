#ifndef OSOBA_HPP_INCLUDED
#define OSOBA_HPP_INCLUDED

class Osoba {
protected:
    DinString ime;
    DinString prezime;
public:
    Osoba() : ime("Nenad"), prezime("Lukic") {}
    // mada bi moglo i samo: Osoba() {}
    // ali sumnjam da je to bas pametno :)
    // ili ovo sto deluje bolje: Osoba() : ime(), prezime() {}

    Osoba (const char* i, const char* p) : ime(i), prezime(p) {}
    Osoba (const DinString& i, const DinString& p) : ime(i), prezime(p) {}
    Osoba (const Osoba& o) : ime(o.ime), prezime(o.prezime) {}
    void predstaviSe () const {
        cout << "Ime: " << ime << endl;
        cout << "Prezime: " << prezime << endl;
    }

    //ako bismo metodu iz osobe prosledili studenta (npr predstavi se)
    //on bi izbacio samo ime i prezime
    //zato se dodaje VIRTUAL ispred metode da bi se u takvim situacijama ispisalo sve za studenta(ime i prezime iz osobe + INDEX)

};

#endif // OSOBA_HPP_INCLUDED
