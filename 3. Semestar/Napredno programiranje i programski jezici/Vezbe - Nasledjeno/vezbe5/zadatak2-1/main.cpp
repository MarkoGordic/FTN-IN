#include <iostream>

// Komentari po klasama su Marijini :)

using namespace std;

#include "dinstring.hpp"
#include "osoba.hpp"
#include "student.hpp"
#include "phdstudent.hpp"

void predstavljanje1(Osoba osoba)
{
    cout << "Predstavljanje (po vrednosti prenos): " << endl;
    osoba.predstaviSe();
    cout << endl;
}

void predstavljanje2(const Osoba &osoba)
{
    cout << "Predstavljanje (po referenci prenos): " << endl;
    osoba.predstaviSe();
    cout << endl;
}

int main()
{
    DinString temp;
    DinString ime("Petar");
    DinString prezime("Peric");
    Osoba o1, o2("Djole", "Mjauic"), o3(ime, prezime), o4(o2);

    // kod ovog predstavljanja nema razlike kad je virtual metoda
    predstavljanje1(o1);
    predstavljanje2(o1);

    Student s1, s2(ime, prezime, 4), s3("Marija", "Todorovic Lukic", 13), s4(o2, 7), s5(s1);

    // dole navedena razlika je moguca ako je predstavljanje virtual u osobi
    // ako virtual nije pristuan tada bismo imali samo predstavljanje osoba
    predstavljanje1(s2); // posto je prenos po vrednosti on ispisuje osobu
    predstavljanje2(s2); // posto je prenos po referenci on ispisuje studenta
                         // to jest ako klase koje nasledjuju osobu se proslede umesto osobe ovde
                         // onda ce se iskoristiti njihovo predstavljanje ako ga imaju

    PhDStudent p1, p2(ime, prezime, 6, 9.0), p3("Jaoj", "Jojic", 18, 7.7), p4(o3, 96, 8.4), p5(s4, 9.6), p6(p2);

    // dole navedena razlika je moguca ako je predstavljanje virtual u osobi
    // ako virtual nije pristuan tada bismo imali samo predstavljanje osoba
    predstavljanje1(p2); // posto je prenos po vrednosti on ispisuje osobu
    predstavljanje2(p2); // posto je prenos po referenci on ispisuje phdstudenta

    // kada predstavljamo direktnim pozivom metoda onda svaka klasa poziva svoj metod
    // ako bismo hteli da od studenta predstavimo osobu onda pisemo s2.Osoba::predstaviSe();
    o1.predstaviSe();
    cout << endl;
    s2.predstaviSe();
    cout << endl;
    p2.predstaviSe();
    cout << endl;
    return 0;
}
