#ifndef ZICARA_HPP_INCLUDED
#define ZICARA_HPP_INCLUDED

enum StanjeZicare {OTVORENA, ZATVORENA};

template <VrstaKarte SEZONA, int BROJ_SEDISTA, int INTERVAL>
class Zicara {
private:
    List <Putnik*> putnici;
    StanjeZicare stanje;
    int ukupnoVoznji;
    int ukupnoMinuta;
public:
    Zicara() : stanje(ZATVORENA) {}

    void otvori() {
        stanje = OTVORENA;
        ukupnoVoznji = 0;
        ukupnoMinuta = 0;
    }

    void zatvori() {
        stanje = ZATVORENA;
        putnici.clear();
    }

    bool dodajPutnika(Putnik *putnik) {
        if (SEZONA != putnik->getVrstaKarte())
            return false;
        Putnik *temp;
        for (int i = 1; i<=putnici.size(); i++){
            putnici.read(i, temp);
            if (putnik->getMB() == temp->getMB())
                return false;
        }
        return putnici.add(putnici.size() + 1, putnik);
    }

    int brojPutnika() const {
        return putnici.size();
    }

    bool preveziTuru() {
        if (!brojPutnika() || stanje == ZATVORENA)
            return false;
        int brojPrevezenih = 0;
        while (brojPrevezenih < BROJ_SEDISTA && brojPutnika() > 0) {
            putnici.remove(1);
            brojPrevezenih++;
        }
        ukupnoVoznji += brojPrevezenih;
        if (brojPrevezenih > 0) {
            ukupnoMinuta += INTERVAL;
            return true;
        }
        return false;
    }

    friend ostream& operator<<(ostream& out, const Zicara<SEZONA, BROJ_SEDISTA, INTERVAL>& zicara) {
        out << "--------------------------" << endl;
        out << "ZICARA" << endl << "Sezona: ";
        switch (SEZONA) {
            case LETO: out << "LETO"; break;
            case SKI: out << "SKI"; break;
            case SKI_OPENING: out << "SKI_OPENING"; break;
        }
        out << endl << "Broj sedista: " << BROJ_SEDISTA << endl;
        out << "Stanje: " << (zicara.stanje == OTVORENA ? "OTVORENA" : "ZATVORENA") << endl;
        out << "Trajanje jedne voznje: " << INTERVAL << endl;
        out << "Ukupno voznji: " << zicara.ukupnoVoznji << endl;
        out << "Radno vreme u satima: " << zicara.getRadnoVreme() << endl;
        out << "Broj osoba u redu: " << zicara.brojPutnika() << endl;
        if (zicara.brojPutnika() == 0) {
            out << "Nema osoba u redu!" << endl;
        }
        else {
            Putnik *temp;
            for (int i = 1; i <= zicara.putnici.size(); i++){
                zicara.putnici.read(i, temp);
                out << *temp;
            }
        }
        out << "--------------------------" << endl;
        return out;
    }

    double getRadnoVreme() const {
        return (double)ukupnoMinuta / 60;
    }
};

#endif // ZICARA_HPP_INCLUDED
