#ifndef PROFESOR_HPP_INCLUDED
#define PROFESOR_HPP_INCLUDED

class Profesor : public Osoba {
private:
    DinString predmet;
public:
    Profesor () : predmet("NPPJ") {}
    Profesor (const DinString &i, const DinString &p, const DinString &pr) : Osoba(i, p), predmet(pr) {}
    Profesor (const Profesor& p) : Osoba(p), predmet(p.predmet) {}

    void predstaviSe () const {
        Osoba::predstaviSe();
        cout << "Predajem: " << predmet << "." << endl;
    }
};

#endif // PROFESOR_HPP_INCLUDED
