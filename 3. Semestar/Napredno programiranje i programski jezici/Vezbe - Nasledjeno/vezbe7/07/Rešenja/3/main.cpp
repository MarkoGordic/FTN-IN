#include "ucionica.hpp"

int main()
{
    cout << "Testiranje klase Osoba" << endl << endl;

    Osoba o;
    o.predstaviSe();

    Osoba o1 ("Petar", "Petrovic");
    o1.predstaviSe();

    Osoba o2(o1);
    o2.predstaviSe();

    cout << endl << endl;
    cout << "Testiranje klase Student" << endl << endl;

    Student s;
    s.predstaviSe();

    Student s1("Marko", "Markovic", 12345);
    s1.predstaviSe();

    Student s2(s1);
    s2.predstaviSe();


    cout << endl << endl;
    cout << "Testiranje klase Profesor" << endl << endl;

    Profesor p;
    p.predstaviSe();

    Profesor p1("Ivana", "Ivanovic", "Objektno programiranje");
    p1.predstaviSe();

    Profesor p2(p1);
    p2.predstaviSe();


    cout << endl << endl;
    cout << "Testiranje klase Ucionica" << endl << endl;

    Ucionica u("FTN-U1", 5);
    u.ispis();

    if(u.dodaj(p1)) {
        cout << "Uspesno dodavanje." << endl;
    } else {
        cout << "Neuspesno dodavanje." << endl;
    }

    if(u.dodaj(p2)) {
        cout << "Uspesno dodavanje." << endl;
    } else {
        cout << "Neuspesno dodavanje." << endl;
    }

    if(u.dodaj(s1)) {
        cout << "Uspesno dodavanje." << endl;
    } else {
        cout << "Neuspesno dodavanje." << endl;
    }

    if(u.dodaj(s2)) {
        cout << "Uspesno dodavanje." << endl;
    } else {
        cout << "Neuspesno dodavanje." << endl;
    }

    if(u.dodaj(o1)) {
        cout << "Uspesno dodavanje." << endl;
    } else {
        cout << "Neuspesno dodavanje." << endl;
    }

    if(u.dodaj(o2)) {
        cout << "Uspesno dodavanje." << endl;
    } else {
        cout << "Neuspesno dodavanje." << endl;
    }

    u.ispis();

    return 0;
}
