#ifndef KARTA_HPP_INCLUDED
#define KARTA_HPP_INCLUDED

enum VrstaKarte {LETO, SKI, SKI_OPENING};

class Karta {
private:
    int brojKarte;
    VrstaKarte vrsta;
public:
    Karta () : brojKarte(0), vrsta(LETO) {}

    Karta (int bk, VrstaKarte v) : brojKarte(bk), vrsta(v) {}

    Karta (const Karta& k) : brojKarte(k.brojKarte), vrsta(k.vrsta) {}

    int getBrojKarte () const {
        return brojKarte;
    }

    VrstaKarte getVrstaKarte () const {
        return vrsta;
    }

    friend ostream& operator<<(ostream& out, const Karta& k) {
        out << "Karta: " << k.vrsta;
        switch (k.vrsta) {
        case SKI: out << "SKI"; break;
        case LETO: out << "LETO"; break;
        case SKI_OPENING: out << "SKI_OPENING"; break;
        }
        out << ", broj: " << k.brojKarte << endl;
        return out;
    }
};

#endif // KARTA_HPP_INCLUDED
