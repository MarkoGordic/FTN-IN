#ifndef PUTNIK_HPP_INCLUDED
#define PUTNIK_HPP_INCLUDED

class Putnik {
protected:
    Karta karta;
    DinString mb;
    DinString ime;
public:
    Putnik () : karta(), mb(""), ime("") {}

    Putnik (int bk, VrstaKarte v, const DinString& m, const DinString& i)
        : karta(bk, v), mb(m), ime(i) {}

    DinString getMB () const {
        return mb;
    }

    VrstaKarte getVrstaKarte () const {
        return karta.getVrstaKarte();
    }

    virtual DinString toString() const {
        return mb + " " + ime;
    }

    friend ostream& operator<<(ostream& out, const Putnik& p) {
        out << "Putnik: " << p.toString() << endl;
        out << p.karta << endl;
        return out;
    }
};

#endif // PUTNIK_HPP_INCLUDED
