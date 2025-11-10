#include <iostream>
#include <ctime>

using namespace std;

#include "list.hpp"
#include "dinstring.hpp"
#include "test.hpp"
#include "kolokvijum.hpp"
#include "predmet.hpp"
#include "student.hpp"

int main()
{
    srand(time(0));
    /*DinString d("kolokvijum 2");
    Test t1, t2(d, 25);
    cout << t1 << endl;
    cout << t2 << endl;*/

    cout << "KOLOKVIJUM TESTIRANJE" << endl;
    Kolokvijum k, k1("K1"), k2("K2"), k3("K3");
    cout << k1 << endl;
    cout << k2 << endl;
    cout << "Broj poena na testic: " << k2.getPoeni() << endl;
    cout << (k2.polozio() ? "polozio" : "nije polozio") << endl;

    cout << endl << "PREDMET TESTIRANJE" << endl;
    Predmet p1, p2("NPPJ"), p3("LPRS");
    p2.dodajTest(k1);
    p2.dodajTest(k2);
    p2.dodajTest(k3);
    p2.ispis();
    p1.ispis();
    p3.dodajTest(k2);
    p3.dodajTest(k3);
    p3.ispis();
    Predmet p4(p2);
    p4.ispis();

    cout << "Predmet: " << p2.getNaziv() << endl;
    cout << (p2.polozio() ? "polozen" : "nije polozen") << endl;
    cout << "Broj poena: " << p2.getUkupniPoeni() << endl;

    cout << endl << "STUDENT TESTIRANJE" << endl;
    Student s(p2, p3);
    s.ispis();

    return 0;
}
