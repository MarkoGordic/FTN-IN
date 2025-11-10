#include <iostream>
#include "odeca.hpp"
#include "voce.hpp"
#include "grad.hpp"
using namespace std;

int Odeca::brojVelikeOdece = 0;

int main()
{

    cout << "--- Odeca ---" << endl;
    Odeca o1(XL, MAJICA, 1000, "Zuta majica");
    cout << "Broj velike odece: " << o1.getBrojVelikeOdece() << endl;

    o1.ispisi();
    o1.izracunajPopust();
    cout << "--- Nakon popusta ---" << endl;
    o1.ispisi();

    cout << "--- Voce ---" << endl;
    Voce v1("Jabuka", "Srbija", 4, 100);
    Voce v2("Banana", "Brazil", 15, 300);
    v1.ispisi();
    v1.izracunajPopust();
    cout << "--- Nakon popusta ---" << endl;
    v1.ispisi();

    cout << "--- Prodavnica --- " << endl;
    Prodavnica p("Maxi");
    p.dodajProizvod(o1);
    p.dodajProizvod(v1);
    p.dodajProizvod(v2);

    cout << p << endl;
    cout << "Akcija!!!" << endl;
    p.akcija(700);

    cout << p << endl;

    p.obrisiProizvod(1);
    p.obrisiProizvod("Zuta majica");
    cout << "--- Brisanje proizvoda ---" << endl;
    cout << p << endl;


    Prodavnica p2("Prodavnica svega i svacega");
    Voce v3("Kruske", "Srbija", 30,150);
    Odeca o2(M,PANTALONE,1200,"Crvene pantalone");
    Odeca o3(XL, PANTALONE, 1200, "Plave pantalone");

    p2.dodajProizvod(v3);
    p2.dodajProizvod(o2);
    p2.dodajProizvod(o3);

    cout << "--- Grad --- " << endl;

    Grad g;
    g.dodajProdavnicu(p);
    g.dodajProdavnicu(p2);

    g.ispisiNajjeftinijuProdavnicu();

    return 0;
}

