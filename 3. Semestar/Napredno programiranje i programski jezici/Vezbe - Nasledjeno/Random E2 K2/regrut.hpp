#ifndef REGRUT_HPP_INCLUDED
#define REGRUT_HPP_INCLUDED

enum Iskustvo {begginer, experienced, veteran};

class Regrut {
protected:
    DinString ime;
    DinString prezime;
    double godineSluzbe;
    Iskustvo iskustvo;
    double najam;
public:
    Regrut(const DinString& i, const DinString& p, double g, Iskustvo is, double n)
        : ime(i), prezime(p), godineSluzbe(g), iskustvo(is), najam(n) {}

    DinString getImePrezime() const {
        return ime + " " + prezime;
    }

    double getNajam() const {
        return najam;
    }

    virtual double getGodineSluzbe() const = 0;

    virtual void predstaviSe() const {
        cout << "Regrut: " << getImePrezime() << endl;
        cout << "Godine sluzbe: " << godineSluzbe << endl;
        cout << "Iskustvo: ";
        switch (iskustvo){
            case begginer: cout << "begginer"; break;
            case experienced: cout << "experienced"; break;
            case veteran: cout << "veteran"; break;
        }
        cout << endl;
    }
};

#endif // REGRUT_HPP_INCLUDED
