#ifndef STRELAC_HPP_INCLUDED
#define STRELAC_HPP_INCLUDED

enum OruzjeStrelca {pracka, luk, samostrel};

class Strelac : public Regrut{
private:
    OruzjeStrelca oruzje;
    static int promenjenoOruzje;
public:
    Strelac(const DinString& i, const DinString& p, double g, Iskustvo is, double n, OruzjeStrelca o)
        : Regrut(i, p, g, is, n), oruzje(o) {}

    double getGodineSluzbe() const {
        return godineSluzbe;
    }

    virtual void predstaviSe() const {
        cout << "--- STRELAC ---" << endl;
        Regrut::predstaviSe();
        cout << "Oruzje: ";
        switch (oruzje){
            case pracka: cout << "pracka"; break;
            case luk: cout << "luk"; break;
            case samostrel: cout << "samostrel"; break;
        }
        cout << endl << "UKUPNO PROMENJENIH ORUZJA KOD STRELACA: " << promenjenoOruzje << endl;
        cout << endl;
    }

    bool unaprediOruzje(double najam_dodatak) {
        if (oruzje == pracka && godineSluzbe > 2) {
            oruzje = luk;
            najam += najam_dodatak * 0.25;
            promenjenoOruzje++;
            return true;
        }
        else if (oruzje == luk && godineSluzbe > 5) {
            oruzje = samostrel;
            najam += najam_dodatak;
            promenjenoOruzje++;
            return true;
        }
        najam += najam_dodatak;
        return false;
    }
};

int Strelac::promenjenoOruzje = 0;

#endif // STRELAC_HPP_INCLUDED
