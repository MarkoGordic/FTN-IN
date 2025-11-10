#include <iostream>

using namespace std;

#include "dinstring.hpp"
#include "list.hpp"
#include "dete.hpp"
#include "paketic.hpp"
#include "novogodisnjipaketic.hpp"
#include "dedamraz.hpp"

int main()
{
    Dete d1, d2("Miki", DECAK, 10, true), d3(d2);
    cout << d2 << endl;
    cout << d2.getNadimak() << d2.getPol() << d2.getUzrast() << d2.getZasluzenNovogodisnjiPaketic() << endl;

    /*Paketic p1, p2("lepooo", d3);
    cout << p1.getStatus() << endl;
    p1.spakuj();*/

    NovogodisnjiPaketic np1, np2("lepoooooo", d2, 7);
    cout << np1.getNapravljeniNovogodisnjiPaketici() << endl;
    cout << np1.getMinimalanUzrast() << endl;
    cout << np1.getNapravljeniNovogodisnjiPaketici() << endl;

    np2.ispisi();
    np2.isporuci();
    np1.isporuci();

    DedaMraz dm;
    dm.ispis();
    dm.dodaj("aaaa", d2, 5, DECAK);
    dm.dodaj("LL", d2, 6, DECAK);
    dm.dodaj("EE", d2, 7, DECAK);
    dm.dodaj("E", d2, 8, DECAK);
    dm.dodaj("E", d2, 9, DECAK);
    dm.ispis();
    dm.izbaci(7);
    dm.ispis();
    dm.dodaj("E", d2, 8, DECAK);
    dm.dodaj("E", d2, 9, DECAK);
    dm.ispis();
    cout << dm.prosecanMinimalanUzrast() << endl;

    {
        NovogodisnjiPaketic np3;
        cout << np1.getNapravljeniNovogodisnjiPaketici() << endl;
    }
    cout << np1.getNapravljeniNovogodisnjiPaketici() << endl;


    return 0;
}
