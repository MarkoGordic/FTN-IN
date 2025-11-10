#include <iostream>

// Komentari po klasama su Marijini :)

using namespace std;

#include "pravougaonik.hpp"
#include "elipsa.hpp"
#include "kvadrat.hpp"
#include "krug.hpp"
#include "oblik.hpp"

// radimo prenos po referenci za klasu Figura kako bi on mogao sam da skonta da je prosledjeni
// parametar tipa nekog naslednika od Figure i da onda pristupi njegovoj povrsini i obimu :)
// ovo je ono o cemu je Dunja pricala, da kompajler sam skonta sta treba da zove :)
void ispisP (const Figura& fig) {
    cout << "Povrsina: " << fig.getP() << endl;
}

void ispisO (const Figura& fig) {
    cout << "Obim: " << fig.getO() << endl;
}

int main()
{
    Elipsa e1, e2(3, 4), e3(e1);
    ispisP(e2);
    ispisO(e2);

    Pravougaonik p1, p2(3, 4), p3(p1);
    ispisP(p2);
    ispisO(p2);

    Kvadrat kv1, kv2(6), kv3(kv1);
    ispisP(kv2);
    ispisO(kv2);

    Krug k1, k2(4), k3(k1);
    ispisP(k2);
    ispisO(k2);

    Oblik o1, o2(4), o3(o1);
    cout << "Povrsina: " << o2.getP() << endl;
    cout << "Obim: " << o2.getO() << endl;
    return 0;
}
