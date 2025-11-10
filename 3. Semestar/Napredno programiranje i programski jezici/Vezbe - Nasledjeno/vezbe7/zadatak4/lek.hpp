#ifndef LEK_HPP_INCLUDED
#define LEK_HPP_INCLUDED

class Lek : public Artikal {
private:
    long jkl;
    DinString naziv;
    double jedinicnaCena;
    int kolicina;
public:
    Lek () : naziv("") {
        jkl = 0; jedinicnaCena = 0; kolicina = 0;
    }

    Lek (long jkl1, const char ime[], double jc1, int kolicina1) : naziv(ime) {
        jkl = jkl1; jedinicnaCena = jc1; kolicina = kolicina1;
    }

    Lek (long jkl1, const DinString &ime, double jc1, int kolicina1) : naziv(ime) {
        jkl = jkl1; jedinicnaCena = jc1; kolicina = kolicina1;
    }

    Lek (const Lek& l) : naziv(l.naziv) {
        jkl = l.jkl; jedinicnaCena = l.jedinicnaCena; kolicina = l.kolicina;
    }

    double vrednostArtikla () const {
        return kolicina * jedinicnaCena;
    }

    friend ostream& operator<<(ostream& out, const Lek &lek) {
        out << "LEK" << endl;
        out << "jkl: " << lek.jkl << endl;
        out << "naziv: " << lek.naziv << endl;
        out << "jedinicnaCena: " << lek.jedinicnaCena << endl;
        out << "kolicina: " << lek.kolicina << endl;
        return out;
    }
};

#endif // LEK_HPP_INCLUDED
