#include <iostream>

using namespace std;

#include "list.hpp"
#include "osoba.hpp"
#include "student.hpp"
#include "profesor.hpp"
#include "ucionica.hpp"

int main()
{
    cout << "Osoba" << endl;

    Osoba o1, o2("Marko", "Markovic"), o3(o2);
    o1.predstaviSe();
    o2.predstaviSe();
    o3.predstaviSe();

    cout << endl << "Student" << endl;
    Student s1, s2("Nenad", "Lukic", 17), s3("Marija", "Todorovic", 13), s4(s1);
    s1.predstaviSe();
    s2.predstaviSe();
    s3.predstaviSe();
    s4.predstaviSe();

    cout << endl << "Profesor" << endl;
    Profesor p1, p2("Marko", "Markovic", "OPPJ"), p3(p2);
    p1.predstaviSe();
    p2.predstaviSe();
    p3.predstaviSe();

    cout << endl << "Ucionica" << endl;
    Ucionica u1("MI A2-3", 6);
    u1.ispisi(); cout << endl << endl;
    u1.dodaj(o1);
    u1.dodaj(o2);
    u1.dodaj(s1);
    u1.dodaj(s2);
    u1.dodaj(p1);
    u1.dodaj(p2);
    if (u1.dodaj(p3)) {
        cout << "Dodat." << endl;
    }
    else {
        cout << "Nije dodat." << endl;
    }
    cout << endl << endl;
    u1.ispisi();
    return 0;
}
