#ifndef PREDMET_HPP_INCLUDED
#define PREDMET_HPP_INCLUDED

class Predmet {
private:
    DinString naziv;
    List <Test*> testovi;
public:
    Predmet () : naziv() {}

    Predmet (const DinString& ime) : naziv(ime) {}

    Predmet (const char ime[]) : naziv(ime) {}

    Predmet (const Predmet& p) : naziv(p.naziv) {
        testovi.clear();
        for (int i = 1; i <= p.testovi.size(); i++) {
            Test *pom;
            p.testovi.read(i, pom);
            testovi.add(i, pom);     /// htedoh deep copy
        }
    }

    /// moze i ovo Predmet (const Predmet& p) : naziv(p.naziv), testovi(p.testovi) {}

    void dodajTest (Test& t) {
        testovi.add(testovi.size()+1, &t);  /// iz maina se prosledjuje referenca od koje uzimamo adresu
    }

    bool polozio () const {
        int suma = 0;
        for (int i = 1; i <= testovi.size(); i++) {
            Test *pom;
            testovi.read(i, pom);
            if (pom->polozio()) {
                suma += pom->getPoeni();
            }
            else {
                return false;
            }
        }
        if (suma > 55)
            return true;
        return false;
    }

    int getUkupniPoeni () const {
        int suma = 0;
        for (int i = 1; i <= testovi.size(); i++) {
            Test *pom;
            testovi.read(i, pom);
            suma += pom->getPoeni();
        }
        return suma;
    }

    DinString getNaziv () const {
        return naziv;
    }

    void ispis () const {
        cout << "Predmet: " << naziv << endl;
        cout << "-----------------" << endl;
        for (int i = 1; i <= testovi.size(); i++) {
            Test *pom;
            testovi.read(i, pom);
            cout << *pom << endl;
        }
        cout << "-----------------" << endl;
    }
};

#endif // PREDMET_HPP_INCLUDED
