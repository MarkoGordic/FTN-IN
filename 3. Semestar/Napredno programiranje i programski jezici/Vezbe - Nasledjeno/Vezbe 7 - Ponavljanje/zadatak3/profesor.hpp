#ifndef PROFESOR_HPP_INCLUDED
#define PROFESOR_HPP_INCLUDED

class Profesor : public Osoba {
private:
    DinString predmet;
public:
    Profesor() : Osoba(), predmet("nppj") {}

    Profesor(const Osoba& o, const DinString& pr) : Osoba(o), predmet(pr) {}

    Profesor(const DinString& i, const DinString& p, const DinString& pr) : Osoba(i, p), predmet(pr) {}

    Profesor(const Profesor& p) : Osoba(p.ime, p.prezime), predmet(p.predmet) {}

    void ispis() const {
        Osoba::ispis();
        cout << "Predajem predmet zvani " << predmet << "." << endl;
    }
};

#endif // PROFESOR_HPP_INCLUDED
