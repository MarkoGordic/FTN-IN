#include <iostream>

// Komentari po klasama su Marijini :)

using namespace std;

#include "pravougaonik.hpp"
#include "elipsa.hpp"
#include "kvadrat.hpp"
#include "krug.hpp"
#include "oblik.hpp"
#include "pravilanoblik.hpp"

// radimo prenos po referenci za klasu Figura kako bi on mogao sam da skonta da je prosledjeni
// argument tipa nekog naslednika od Figure i da onda pristupi njegovoj povrsini i obimu :)
// ovo je ono o cemu je Dunja pricala, da kompajler sam skonta sta treba da zove :)
void ispisP (const Figura& fig) {
    cout << "Povrsina: " << fig.getP() << endl;
}

void ispisO (const Figura& fig) {
    cout << "Obim: " << fig.getO() << endl;
}

// e da, i nazivamo funkcije isto, samo imaju drugacije parametre, cisto da pokazemo i overloading funkcija :)
void ispisP (const Oblik& oblik) {
    cout << "Povrsina: " << oblik.getP() << endl;
}

void ispisO (const Oblik& oblik) {
    cout << "Obim: " << oblik.getO() << endl;
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

    Oblik o1, o2(6.4, 3), o3(o1);
    ispisP(o2);
    ispisO(o2);

    PravilanOblik po1, po2(4), po3(po1);
    ispisP(po2);
    ispisO(po2);

    return 0;
}
