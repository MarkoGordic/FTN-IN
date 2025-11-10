#ifndef DIJAMANT_HPP_INCLUDED
#define DIJAMANT_HPP_INCLUDED

class Dijamant {
private:
    double vrednost;
    double brojKarata;
public:
    Dijamant () : vrednost(10.3), brojKarata(2.42) {}

    Dijamant (double v, double bk) : vrednost(v), brojKarata(bk) {}

    Dijamant (const Dijamant& d) :  vrednost(d.vrednost), brojKarata(d.brojKarata) {}

    friend ostream& operator<<(ostream& out, const Dijamant& d) {
        out << "Dijamant" << endl;
        out << "Vrednost: " << d.vrednost << endl;
        out << "Broj karata: " << d.brojKarata << endl;
        return out;
    }
};

#endif // DIJAMANT_HPP_INCLUDED
