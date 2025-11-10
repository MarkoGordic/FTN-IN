#ifndef UCIONICA_HPP_INCLUDED
#define UCIONICA_HPP_INCLUDED

class Ucionica {
private:
    List <Osoba*> osobe;
    int maxOsoba;
    DinString naziv;
public:
    Ucionica () : maxOsoba(5), naziv("MI A2-3") {}

    bool dodajOsobu (Osoba& o) {
        if (osobe.size() >= maxOsoba)
            return false;
        return osobe.add(1, &o);
    }

    void ispis() const {
        cout << "Ucionica: " << naziv << endl;
        if (!osobe.size()) {
            cout << "Ucionica je prazna!" << endl;
            return;
        }
        Osoba* temp;
        for (int i = 1; i <= osobe.size(); i++) {
            osobe.read(i, temp);
            temp->ispis();
        }
    }
};

#endif // UCIONICA_HPP_INCLUDED
