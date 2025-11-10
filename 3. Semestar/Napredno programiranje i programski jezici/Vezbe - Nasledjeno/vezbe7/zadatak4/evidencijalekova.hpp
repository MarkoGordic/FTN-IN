#ifndef EVIDENCIJALEKOVA_HPP_INCLUDED
#define EVIDENCIJALEKOVA_HPP_INCLUDED

class EvidencijaLekova {
private:
    DinString nazivApoteke;
    DinString datum;
    List<Lek> lekovi;
public:
    EvidencijaLekova () {}
    EvidencijaLekova (const DinString& naziv, const DinString& date) : nazivApoteke(naziv), datum(date) {}

    bool dodajNaKraj (long jkl1, const char ime[], double jc1, int kolicina1) {
        Lek lek (jkl1, ime, jc1, kolicina1);
        return lekovi.add(lekovi.size() + 1, lek);
    }

    bool dodajNaPocetak (const Lek &lek) {
        return lekovi.add(1, lek);
    }

    bool obrisiLek (int pozicija) {
        return lekovi.remove(pozicija);
    }

    void sortirajLekove () {
        Lek l1, l2;
        for (int i = 1; i <= lekovi.size(); i++) {
            for (int j = i + 1; j <= lekovi.size(); j++) {
                lekovi.read(i, l1);
                lekovi.read(j, l2);
                if (l1.vrednostArtikla() > l2.vrednostArtikla()) {
                    lekovi.remove(i);
                    lekovi.add(i, l2);
                    lekovi.remove(j);
                    lekovi.add(j, l1);
                }
            }
        }
    }


    friend ostream& operator<<(ostream& out, const EvidencijaLekova &el) {
        // 1. nacin
        // out << evidencija.lekovi (ne moze se koristiti ako nije preklopljen operator ispisa u lekovima)
        out << "APOTEKA" << endl;
        out << "Naziv: " << el.nazivApoteke << endl;
        out << "Datum evidencija: " << el.datum << endl;
        out << "Evidencija lekova" << endl;
        out << "------------------------------------------" << endl;
        for (int i = 1; i <= el.lekovi.size(); i++) {
            Lek lek;
            el.lekovi.read(i, lek);
            out << lek << endl;
        }
        out << "------------------------------------------" << endl;

        return out;
        // 2. nacin
        // klasicno iteriramo kroz el i ispisemo
    }
};

#endif // EVIDENCIJALEKOVA_HPP_INCLUDED
