#ifndef IGRAC_HPP_INCLUDED
#define IGRAC_HPP_INCLUDED

class Igrac {
private:
    int poeni;
    int brojPartija;
public:
    Igrac (int p = 0, int bp = 0) {
        poeni = p;
        brojPartija = bp;
    }

    Igrac (const Igrac& i) {
        poeni = i.poeni;
        brojPartija = i.brojPartija;
    }

    void dodajPoene (int dodatak) {
        poeni += dodatak;
    }

    void odigrajPartiju () {
        brojPartija++;
    }

    void resetuj () {
        poeni = 0;
        brojPartija = 0;
    }

    void ispis () const {
        cout << "----- IGRAC -----" << endl;
        cout << "Poeni: " << poeni << endl;
        cout << "Broj partija: " << brojPartija << endl;
        cout << "-----------------" << endl << endl;
    }

    int getPoeni () const {
        return poeni;
    }

    int getBrojPartija () const {
        return brojPartija;
    }

    void setPoeni (int p) {
        poeni = p;
    }

    void setBrojPartija (int bp) {
        brojPartija = bp;
    }
};

#endif // IGRAC_HPP_INCLUDED
