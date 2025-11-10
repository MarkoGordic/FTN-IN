#include <iostream>

using namespace std;

#include "dinstring.hpp"
#include "list.hpp"
#include "karta.hpp"
#include "putnik.hpp"
#include "putnikdete.hpp"
#include "zicara.hpp"

int main()
{
    cout << "TESTIRANJE KARTE" << endl;
    Karta k1, k2(101, SKI_OPENING);
    cout << k1 << endl;
    cout << k2 << endl;
    cout << k2.getBrojKarte() << endl;
    cout << k2.getVrsta() << endl;

    cout << endl << "TESTIRANJE PUTNIKA" << endl;
    Putnik p1, p2(486, SKI, "48456123", "Nenad"), p3(485, SKI, "58496134", "Marija"), p4(p1), p5(86, SKI, "214545", "Iva");
    cout << p2 << endl;
    cout << p2.getVrstaKarte() << endl;
    cout << p2.getMB() << endl;
    cout << p2.toString() << endl;

    cout << endl << "TESTIRANJE DETE PUTNIKA" << endl;
    PutnikDete pd1, pd2(87, SKI, "41554", "Relja", "48456123"), pd3(p5, "58496134");
    cout << pd2.toString() << endl;

    cout << endl << "TESITRANJE ZICARE" << endl;
    Zicara<SKI, 2, 5> z1;
    Zicara<LETO, 2, 5> z2;
    z1.otvori();
    z1.zatvori();
    z1.otvori();
    cout << z1 << endl;
    z1.dodajPutnika(&p2);
    z1.dodajPutnika(&p2);
    z1.dodajPutnika(&p3);
    cout << (z1.dodajPutnika(&pd2) ? "TRUE" : "FALSE") << endl;
    cout << z1 << endl;
    cout << "radno vreme: " << z1.getRadnoVreme() << endl;
    cout << "broj putnika: " << z1.brojPutnika() << endl;
    z1.preveziTuru();
    z1.preveziTuru();
    cout << z1 << endl;

    z2.dodajPutnika(&p2);
    cout << z2 << endl;
    return 0;
}
