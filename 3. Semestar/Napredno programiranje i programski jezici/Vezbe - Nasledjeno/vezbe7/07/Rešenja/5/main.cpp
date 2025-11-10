#include "student.hpp"
#include <ctime>

int main()
{
    srand(time(NULL));

    cout << "Testiranje klase Kolokvijum" << endl << endl;
    Kolokvijum k, k1("K1"), k2("K2"), k3("K3"), k4("K4");

    k.ispis();
    cout << "Polozio: " << (k.polozio() ? "DA" : "NE") << endl << endl;

    k1.ispis();
    cout << "Polozio: " << (k1.polozio() ? "DA" : "NE") << endl << endl;

    k2.ispis();
    cout << "Polozio: " << (k2.polozio() ? "DA" : "NE") << endl << endl;

    k3.ispis();
    cout << "Polozio: " << (k3.polozio() ? "DA" : "NE") << endl << endl;

    k4.ispis();
    cout << "Polozio: " << (k4.polozio() ? "DA" : "NE") << endl << endl;


    cout << endl << endl;
    cout << "Testiranje klase Predmet" << endl;

    Predmet p, p2("OP"), p3("MISS");

    p.ispis();
    p2.ispis();
    p3.ispis();

    p2.dodajTest(k1);
    p2.ispis();

    p2.dodajTest(k2);
    p2.dodajTest(k3);
    p2.dodajTest(k4);
    p2.ispis();

    cout << "Ukupno bodova osvojeno: " << p2.getUkupniPoeni() << endl;
    cout << (p2.polozio() ? "Polozio OP" : "Nije polozio OP") << endl;

    cout << endl << endl;
    Predmet p4(p2);
    p4.ispis();


    cout << endl << endl ;
    cout << "Testiranje klase Student" << endl;

    Student s(p2, p3);
    s.ispis();

    return 0;
}
