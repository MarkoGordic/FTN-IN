#ifndef ZICARA_HPP_INCLUDED
#define ZICARA_HPP_INCLUDED

enum StanjeZicare {OTVORENA, ZATVORENA};

template <VrstaKarte SEZONA, int BROJ_SEDISTA, int INTERVAL>
class Zicara {
private:
    List<Putnik*> putnici;
    StanjeZicare stanje;
    int ukupnoVoznji;
    int ukupnoMinuta;
public:
    Zicara () : stanje(ZATVORENA), ukupnoMinuta(0), ukupnoVoznji(0) {}

    void otvori() {
        stanje = OTVORENA;
        ukupnoMinuta = 0;
        ukupnoVoznji = 0;
    }

    void zatvori() {
        stanje = ZATVORENA;
        putnici.clear();
    }

    bool dodajPutnika(Putnik* p) {
        if (p->getVrstaKarte() != SEZONA)
            return false;
        Putnik* temp;
        for (int i = 1; i<=putnici.size(); i++){
            putnici.read(i, temp);
            if (temp->getMB() == p->getMB())
                return false;
        }
        return putnici.add(putnici.size() + 1, p);
    }

    int brojPutnika() const {
        return putnici.size();
    }

    bool preveziTuru() {
        if (stanje == ZATVORENA || brojPutnika() == 0)
            return false;
        int brojPrevezenih = 0;
        for (int i = 1; i <= BROJ_SEDISTA; i++) {
            if(putnici.remove(i)) {
                brojPrevezenih++;
            }
        }
        if (brojPrevezenih) {
            ukupnoVoznji += brojPrevezenih;
            ukupnoMinuta += INTERVAL;
            return true;
        }
        return false;
    }

    friend ostream& operator<<(ostream& out, const Zicara<SEZONA, BROJ_SEDISTA, INTERVAL>& z) {
        out << "Sezona: ";
        switch (SEZONA) {
        case SKI: out << "SKI"; break;
        case LETO: out << "LETO"; break;
        case SKI_OPENING: out << "SKI_OPENING"; break;
        }
        out << endl << "Broj sedista: " << BROJ_SEDISTA << " Trajanje jedne voznje: " << INTERVAL << endl << " Stanje zicare: " << z.stanje;
        out << " Radno vreme u satima: " << z.getRadnoVreme() << endl << "Broj putnika u redu: " << z.brojPutnika();
        if (z.brojPutnika() > 0){
            for (int i = 1; i <= z.brojPutnika(); i++){
                Putnik *p;
                z.putnici.read(i, p);
                out << *p << endl;
            }
        }
        return out;
    }

    double getRadnoVreme() const {
        return ukupnoMinuta / 60;
    }
};

#endif // ZICARA_HPP_INCLUDED
