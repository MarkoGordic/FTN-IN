#include <iostream>

using namespace std;

#include "trezor.hpp"
#include "dijamant.hpp"

int main()
{
    cout << "Testiranje klase dijamant" << endl;
    Dijamant d1, d2(524.321, 5), d3(d2);
    cout << d2 << endl;

    cout << "Testiranje klase trezor" << endl;
    Trezor<Dijamant, 4> trezorce;
    cout << "Broj popunjenih sefova: " << trezorce.getBrojPopunjenihSefova() << endl;
    cout << "Dodato na poziciju: " << trezorce.ubaciSadrzaj(d1) << endl;
    cout << "Dodato na poziciju: " << trezorce.ubaciSadrzaj(d2) << endl;
    cout << "Dodato na poziciju: " << trezorce.ubaciSadrzaj(d3) << endl;
    cout << "Dodato na poziciju: " << trezorce.ubaciSadrzaj(d1) << endl;
    cout << "Dodato na poziciju: " << trezorce.ubaciSadrzaj(d2) << endl;
    cout << "Broj popunjenih sefova: " << trezorce.getBrojPopunjenihSefova() << endl;
    cout << "Ukloni nesto iz sefa 32: " << trezorce.izbaciSadrzaj(32) << endl;
    cout << "Ukloni nesto iz sefa 3: " << trezorce.izbaciSadrzaj(3) << endl;
    cout << "Ukloni nesto iz sefa 3: " << trezorce.izbaciSadrzaj(3) << endl;
    cout << "Broj popunjenih sefova: " << trezorce.getBrojPopunjenihSefova() << endl;

    return 0;
}
