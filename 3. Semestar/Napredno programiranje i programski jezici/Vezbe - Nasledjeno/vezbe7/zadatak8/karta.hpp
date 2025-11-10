#ifndef KARTA_HPP_INCLUDED
#define KARTA_HPP_INCLUDED

enum VrstaKarte {LETO, SKI, SKI_OPENING};

class Karta {
private:
    int brojKarte;
    VrstaKarte vrsta;
public:
    Karta() : brojKarte(0), vrsta(LETO) {}

    Karta(int bk, VrstaKarte v) : brojKarte(bk), vrsta(v) {}

    int getBrojKarte () const {
        return brojKarte;
    }

    VrstaKarte getVrsta () const {
        return vrsta;
    }

    friend ostream& operator<<(ostream& out, const Karta& karta) {
        out << "------------------------" << endl;
        out << "Karta" << endl;
        out << "Broj karte: " << karta.brojKarte << endl;
        out << "Vrsta karte: ";
        switch (karta.vrsta) {
            case LETO: out << "LETO"; break;
            case SKI: out << "SKI"; break;
            case SKI_OPENING: out << "SKI_OPENING"; break;
        }
        out << endl << "------------------------" << endl;
        return out;
    }
};

#endif // KARTA_HPP_INCLUDED
