#ifndef ARTIKAL_HPP_INCLUDED
#define ARTIKAL_HPP_INCLUDED

class Artikal {
private:
    DinString naziv;
    double cena;
    static int brojArtikala;
public:
    Artikal(const char niz[], const double c) : naziv(niz), cena(c) {
        brojArtikala++;
    }

    Artikal(const DinString& niz, const double c) : naziv(niz), cena(c) {
        brojArtikala++;
    }

    Artikal(const Artikal& ar) : naziv(ar.naziv), cena(ar.cena) {
        brojArtikala++;
    }

    friend ostream& operator<<(ostream& out, const Artikal& ar) {
        out << "Artikal" << endl;
        out << "Naziv: " << ar.naziv << endl;
        out << "Cena: " << ar.cena << endl;
        out << "Broj artikala: " << ar.brojArtikala << endl;
        return out;
    }

    ~Artikal() {
        brojArtikala--;
    }
};

int Artikal::brojArtikala = 0;

#endif // ARTIKAL_HPP_INCLUDED
