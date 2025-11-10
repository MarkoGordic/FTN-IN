#include <iostream>

using namespace std;

#include "dinstring.hpp"
#include "list.hpp"
#include "artikal.hpp"
#include "lek.hpp"
#include "evidencijalekova.hpp"

int main()
{
    DinString imelekica("lep lekic");
    Lek l1, l2(2645, "joj", 10.5, 10), l3(456, imelekica, 5.6, 100), l4(l2);

    cout << l1 << endl;
    cout << l2 << endl;
    cout << l3 << endl;
    cout << l4 << endl;

    EvidencijaLekova e1("APoteK", "22.11.2023.");
    cout << e1 << endl;
    e1.dodajNaPocetak(l2);
    e1.dodajNaPocetak(l3);
    e1.dodajNaPocetak(l4);
    e1.dodajNaPocetak(l1);
    e1.dodajNaKraj(5234, "kafetin", 10, 1000);
    cout << e1 << endl;

    e1.sortirajLekove();
    cout << e1 << endl;
    return 0;
}
