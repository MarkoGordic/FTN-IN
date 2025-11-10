#include <iostream>

using namespace std;

#include "dinstring.hpp"
#include "list.hpp"
#include "proizvod.hpp"
#include "voce.hpp"
#include "odeca.hpp"
#include "prodavnica.hpp"
#include "grad.hpp"

int main()
{
/*    DinString str("mleko");
    Proizvod p1(5, "kusur zvaka"), p2(100, str);
    p1.ispisi();
    p2.ispisi();*/

    DinString vocka("sljiva"), zemlja("srbija");
    Voce v1("banana", "tanzanija", 35, 3), v2("mandarina", "italija", 50, 0), v3(vocka, zemlja, 20, 8);
    v1.ispisi();
    v2.ispisi();
    v3.ispisi();
    v1.izracunajPopust();
    v2.izracunajPopust();
    v3.izracunajPopust();
    v1.ispisi();
    v2.ispisi();
    v3.ispisi();

    DinString pants("fensi pants");
    Odeca o1("kul majica", 500, XS, MAJICA), o2("manje kul majica", 400, L, MAJICA), o3(pants, 1000, XL, PANTALONE);
    o1.ispisi();
    o2.ispisi();
    o3.ispisi();
    o1.izracunajPopust();
    o2.izracunajPopust();
    o3.izracunajPopust();
    o1.ispisi();
    o2.ispisi();
    o3.ispisi();

    DinString prod("ekstra dzabe");
    Prodavnica p1("dobra prodavnica"), p2(prod), p3("extra prodavnica");
    cout << p1 << endl;
    p1.dodajProizvod(o1);
    p1.dodajProizvod(o1);
    p1.dodajProizvod(v1);
    p1.dodajProizvod(v2);
    p1.dodajProizvod(v3);
    p1.dodajProizvod(o3);
    cout << p1 << endl;
    p1.obrisiProizvod(6);
    p1.obrisiProizvod(2);
    cout << p1 << endl;
    p1.obrisiProizvod(vocka);
    p1.obrisiProizvod("mandarina");
    cout << p1 << endl;
    p1.akcija();
    cout << p1 << endl;

    p2.dodajProizvod(o1);
    p2.dodajProizvod(o2);
    p2.dodajProizvod(v1);
    p2.dodajProizvod(v3);

    p3.dodajProizvod(v1);
    p3.dodajProizvod(v2);
    p3.dodajProizvod(v3);

    Grad g1("Novi Sad"), g2;
    g1.dodajProdavnicu(p1);
    g1.dodajProdavnicu(p2);
    g1.dodajProdavnicu(p3);
    g1.ispisiNajjeftinijuProdavnicu();
    return 0;
}
