#ifndef IGRAC_HPP_INCLUDED
#define IGRAC_HPP_INCLUDED

#define STEP_PARTIJE 1
#define MAX_PARTIJE 10
#define MIN_PARTIJE 0

#define MIN_POENI 0
#define MAX_POENI 10
#define STEP_POENI_RACUNAR 1
#define STEP_POENI_PROTIVNIK 2

class Igrac {
private:
    int poeni;
    int brojPartija;
public:
    Igrac(int p = MIN_POENI, int bp = MIN_PARTIJE) {
        poeni = p;
        brojPartija = bp;
    }

    void dodajPoene(int x) {
        poeni += x;
    }

    void odigrajPartiju() {
        brojPartija += STEP_PARTIJE;
    }

    void resetuj() {
        poeni = MIN_POENI;
        brojPartija = MIN_PARTIJE;
    }

    void ispis() const {
        cout << "IGRAC" << endl;
        cout << "Broj poena: " << poeni << endl;
        cout << "Broj partija: " << brojPartija << endl << endl;
    }

    int getPoeni() const {
        return poeni;
    }

    int getBrojPartija() const {
        return brojPartija;
    }

    void setPoeni(int bp) {
        brojPartija = bp;
    }
};

#endif // IGRAC_HPP_INCLUDED
