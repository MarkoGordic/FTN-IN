#ifndef KARTA_HPP_INCLUDED
#define KARTA_HPP_INCLUDED

enum VrstaKarte { LETO, SKI, SKI_OPENING };

class Karta
{
private:
    int brojKarte;
    VrstaKarte vrsta;
public:
    Karta(): brojKarte(1), vrsta(LETO) {}
    Karta(int bk, VrstaKarte v): brojKarte(bk), vrsta(v) {}

    int getBrojKarte() const
    {
        return brojKarte;
    }

    VrstaKarte getVrstaKarte() const
    {
        return vrsta;
    }

    friend ostream& operator<<(ostream& os, const Karta& k)
    {
        os << "Broj karte: " << k.brojKarte << endl;
        os << "Vrsta karte: ";
        switch(k.vrsta)
        {
        case(LETO):
            os << "LETO" << endl;
            break;
        case(SKI):
            os << "SKI" << endl;
            break;
        case(SKI_OPENING):
            os << "SKI OPENING" << endl;
            break;
        }
        return os;
    }
};


#endif // KARTA_HPP_INCLUDED
