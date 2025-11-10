#ifndef MACEVALAC_HPP_INCLUDED
#define MACEVALAC_HPP_INCLUDED

class Macevalac : public Regrut {
private:
    bool imaDvaMaca;
public:
    Macevalac(const DinString& i, const DinString& p, double g, Iskustvo is, double n, bool idm)
        : Regrut(i, p, g, is, n), imaDvaMaca(idm) {}

    double getGodineSluzbe() const {
        return godineSluzbe;
    }

    virtual void predstaviSe() const {
        cout << "--- MACEVALAC ---" << endl;
        Regrut::predstaviSe();
        cout << "Ima dva maca? " << (imaDvaMaca ? "DA" : "NE");
        cout << endl << endl;
    }

    friend ostream& operator<<(ostream& out, const Macevalac& m) {
        out << "Najam: " << m.najam << endl;
        return out;
    }
};

#endif // MACEVALAC_HPP_INCLUDED
