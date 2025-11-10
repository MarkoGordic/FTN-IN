#ifndef ARTIKAL_HPP_INCLUDED
#define ARTIKAL_HPP_INCLUDED

class Artikal {
private:
    DinString naziv;
    double cena;
    static int brojInstanci;
public:
    Artikal (const char n [], const double c) : naziv(n), cena(c) {
        brojInstanci++;
    }

    Artikal (const DinString& n, const double c) : naziv(n), cena(c) {
        brojInstanci++;
    }

    Artikal (const Artikal& a) : naziv(a.naziv), cena(a.cena) {
        brojInstanci++;
    }

    ~Artikal () {
        brojInstanci--;
    }

    friend ostream& operator<<(ostream& out /*ili os najcesce*/, const Artikal& a) { // mora instanca inace ce povecati brojInstanci!!!
        out << "\nArtikal: " << endl;
        out << "Naziv: " << a.naziv << endl;
        out << "Cena: " << a.cena << endl;
        out << "Broj instanci: " << a.brojInstanci << endl;
        out << endl;
        return out; // mora se vratiti jer nekad moze doci do gresaka
    }

    int get() {
        return brojInstanci;
    }
};

// inicijalizacija mora van klase
int Artikal::brojInstanci = 0;

#endif // ARTIKAL_HPP_INCLUDED
