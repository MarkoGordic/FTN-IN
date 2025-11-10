#ifndef CETA_HPP_INCLUDED
#define CETA_HPP_INCLUDED

class Ceta {
private:
    DinString naziv;
    DinString zadatak;
    int maksimalanBrojRegruta;
    List <Regrut*> regruti;
public:
    Ceta(const DinString& n, const DinString& z, int r)
        : naziv(n), zadatak(z), maksimalanBrojRegruta(r) {}

    void ispisi() const {
        cout << "--- CETA ---" << endl;
        cout << "Naziv: " << naziv << endl;
        cout << "Zadatak: " << zadatak << endl;
        cout << "Maksimalan broj regruta: " << maksimalanBrojRegruta << endl << endl;
        if (regruti.size() == 0){
            cout << "Ceta je prazna!" << endl;
            return;
        }
        Regrut *r;
        for (int i = 1; i <= regruti.size(); i++) {
            regruti.read(i, r);
            r->predstaviSe();
        }
    }

    bool postojiRegrut(const Regrut& r) const {
        Regrut *temp;
        for (int i = 1; i <= regruti.size(); i++) {
            regruti.read(i, temp);
            if (temp->getImePrezime() == r.getImePrezime())
                return true;
        }
        return false;
    }

    bool dodajRegruta(Regrut& r) {
        if (regruti.size() >= maksimalanBrojRegruta || postojiRegrut(r))
            return false;
        return regruti.add(regruti.size() + 1, &r);
    }

    bool izbaciRegruta(Regrut &r) {
        int index = -1;
        Regrut *temp;
        for (int i = 1; i <= regruti.size(); i++) {
            regruti.read(i, temp);
            if (temp->getImePrezime() == r.getImePrezime())     /// gledao sam po imenu i prezimenu kao i u postojiRegrut()
                index = i;                                      /// mogao bi se preklopiti operator== ili proveriti sva polja
        }
        if (index == -1)
            return false;
        return regruti.remove(index);
    }

    double maksimalniNajam() const {
        if (regruti.empty()){
            cout << "Nema regruta u ceti! Maksimalni najam: 0" << endl;
            return 0;
        }
        Regrut *maxN;
        regruti.read(1, maxN);
        Regrut *temp;
        for (int i = 2; i <= regruti.size(); i++) {
            regruti.read(i, temp);
            if (temp->getNajam() > maxN->getNajam())
                maxN = temp;
        }
        cout << "Maksimalni najam je: " << temp->getNajam() << endl;
        return temp->getNajam();
    }
};

#endif // CETA_HPP_INCLUDED
