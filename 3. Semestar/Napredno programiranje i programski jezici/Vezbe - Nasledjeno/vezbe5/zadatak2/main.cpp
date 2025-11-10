#include <iostream>

// Komentari po klasama su Marijini :)

using namespace std;

#include "dinstring.hpp"
#include "osoba.hpp"
#include "student.hpp"
#include "phdstudent.hpp"

int main()
{
    DinString temp;
    DinString ime("Petar");
    DinString prezime("Peric");
    Osoba o1, o2("Djole", "Mjauic"), o3(ime, prezime), o4(o2);

    o1.predstaviSe();
    cout << endl;
    o2.predstaviSe();
    cout << endl;
    o3.predstaviSe();
    cout << endl;
    o4.predstaviSe();
    cout << endl;

    Student s1, s2(ime, prezime, 4), s3("Marija", "Todorovic Lukic", 13), s4(o2, 7), s5(s1);

    s1.predstaviSe();
    cout << endl;
    s2.predstaviSe();
    cout << endl;
    s3.predstaviSe();
    cout << endl;
    s4.predstaviSe();
    cout << endl;
    s5.predstaviSe();
    cout << endl;

    s1.Osoba::predstaviSe(); // ovo ce ispisati samo ime i prezime
                             // to jest, naglasavamo jasno da zelimo ispis osobe
    cout << endl;

    PhDStudent p1, p2(ime, prezime, 6, 9.0), p3("Jaoj", "Jojic", 18, 7.7), p4(o3, 96, 8.4), p5(s4, 9.6), p6(p2);

    p1.predstaviSe();
    cout << endl;
    p2.predstaviSe();
    cout << endl;
    p3.predstaviSe();
    cout << endl;
    p4.predstaviSe();
    cout << endl;
    p5.predstaviSe();
    cout << endl;
    p6.predstaviSe();
    cout << endl;
    return 0;
}
