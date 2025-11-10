#ifndef DIJAMANT_HPP_INCLUDED
#define DIJAMANT_HPP_INCLUDED

class Dijamant {
private:
    double vrednost, brojKarata;
public:
    Dijamant () : vrednost(100), brojKarata(1.1) {}

    Dijamant (double v, double bk) : vrednost(v), brojKarata(bk) {}

    Dijamant (const Dijamant& d) : vrednost(d.vrednost), brojKarata(d.brojKarata) {}

    friend ostream& operator<<(ostream& out, const Dijamant& d) {
        out << "Dijamant vredan: " << d.vrednost << " dolara i ima " << d.brojKarata << " karata." << endl;
        return out;
    }
};

#endif // DIJAMANT_HPP_INCLUDED
