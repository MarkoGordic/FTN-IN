#ifndef PUTNIK_HPP_INCLUDED
#define PUTNIK_HPP_INCLUDED

class Putnik {
protected:
    Karta karta;
    DinString mb;
    DinString ime;
public:
    Putnik() {} // za sve ce se sami konstr bez param pozvati

    Putnik(int br, VrstaKarte v, const DinString& m, const DinString& i) : karta(br, v), mb(m), ime(i) {}

    Putnik(const Putnik& p) : karta(p.karta.getBrojKarte(), p.karta.getVrsta()), mb(p.mb), ime(p.ime) {}

    DinString getMB() const {
        return mb;
    }

    VrstaKarte getVrstaKarte() const {
        return karta.getVrsta();
    }

    virtual DinString toString() const {
        return mb + " " + ime;
    }

    friend ostream& operator<<(ostream& out, const Putnik& putnik) {
        out << "-------------------------" << endl;
        out << "Putnik: " << putnik.toString() << endl;
        out << putnik.karta;
        out << "-------------------------" << endl;
        return out;
    }
};

#endif // PUTNIK_HPP_INCLUDED
