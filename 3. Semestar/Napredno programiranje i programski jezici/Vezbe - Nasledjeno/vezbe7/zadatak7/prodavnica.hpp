#ifndef PRODAVNICA_HPP_INCLUDED
#define PRODAVNICA_HPP_INCLUDED

class Prodavnica {
private:
    DinString naziv;
    List <Proizvod*> proizvodi;
public:
    Prodavnica (const char* ime) : naziv(ime) {}

    Prodavnica (const DinString& ime) : naziv(ime) {}

    bool dodajProizvod (Proizvod& proizvod) {
        bool postoji = false;
        Proizvod* temp;
        for (int i = 1; i <= proizvodi.size(); i++) {
            proizvodi.read(i, temp);
            if (proizvod.getNaziv() == temp->getNaziv())
                postoji = true;
        }
        if (!postoji)
            return proizvodi.add(proizvodi.size() + 1, &proizvod);
        return false;
    }

    bool obrisiProizvod(const DinString& proizvod) {
        Proizvod* temp;
        int index = -1;
        for (int i = 1; i <= proizvodi.size(); i++) {
            proizvodi.read(i, temp);
            if (proizvod == temp->getNaziv()) {
                index = i;
                break;
            }
        }
        return proizvodi.remove(index);
    }

    bool obrisiProizvod(int index) {
        return proizvodi.remove(index);
    }

    void akcija() {
        Proizvod* temp;
        for (int i = 1; i <= proizvodi.size(); i++) {
            proizvodi.read(i, temp);
            temp -> izracunajPopust();
        }
    }

    friend ostream& operator<<(ostream& out, const Prodavnica& prodavnica) {
        out << "Prodavnica: " << prodavnica.naziv << endl;
        Proizvod* temp;
        for (int i = 1; i <= prodavnica.proizvodi.size(); i++) {
            prodavnica.proizvodi.read(i, temp);
            temp -> ispisi();
        }
        return out;
    }

    double getRrosecnaCenaProizvoda () const {
        Proizvod* temp;
        double suma = 0;
        for (int i = 1; i <= proizvodi.size(); i++) {
            proizvodi.read(i, temp);
            suma += temp -> getCena();
        }
        return suma / proizvodi.size();
    }
};

#endif // PRODAVNICA_HPP_INCLUDED
