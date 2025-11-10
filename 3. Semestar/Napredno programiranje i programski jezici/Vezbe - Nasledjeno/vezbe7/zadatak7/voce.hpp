#ifndef VOCE_HPP_INCLUDED
#define VOCE_HPP_INCLUDED

class Voce : public Proizvod {
private:
    DinString zemljaPorekla;
    int rokTrajanja;
public:
    Voce (const char* ime, const char* zemlja, int cena, int rok) : Proizvod(cena, ime), zemljaPorekla(zemlja) {
        rokTrajanja = rok;
    }

    Voce (const DinString& ime, const DinString& zemlja, int cena, int rok) : Proizvod(cena, ime), zemljaPorekla(zemlja) {
        rokTrajanja = rok;
    }

    void izracunajPopust() {
        if (rokTrajanja > 5)
            cena = cena - cena * 0.33;
        else if (rokTrajanja <= 5 && rokTrajanja >= 1)
            cena = cena - cena * 0.66;
        else
            cena = 0;
    }

    void ispisi() {
        Proizvod::ispisi();
        cout << "Zemlja porekla: " << zemljaPorekla << endl;
        cout << "Rok trajanja: " << rokTrajanja << endl << endl;
    }
};

#endif // VOCE_HPP_INCLUDED
