#include <iostream>

#include "trezor.hpp"
#include "dijamant.hpp"

using namespace std;

int main()
{
    Dijamant d1, d2(100000, 50), d3(d2);

    cout << d1 << endl;
    cout << d2 << endl;
    cout << d3 << endl;

    cout << endl;

    Trezor<Dijamant, 100> trezor;

    cout << "Trezor: ubaci D1 rezultat = " << trezor.ubaciSadrzaj(d1) << endl;
    cout << "Trezor: broj popunjenih = " << trezor.getBrojPopunjenihSefova() << endl;
    cout << "Trezor: ubaci D2 rezultat = " << trezor.ubaciSadrzaj(d2) << endl;
    cout << "Trezor: broj popunjenih = " << trezor.getBrojPopunjenihSefova() << endl;
    cout << "Trezor: ubaci D3 rezultat = " << trezor.ubaciSadrzaj(d3) << endl;
    cout << "Trezor: broj popunjenih = " << trezor.getBrojPopunjenihSefova() << endl;

    cout << "Trezor: izbaci 50 rezultat = " << trezor.izbaciSadrzaj(50) << endl;
    cout << "Trezor: broj popunjenih = " << trezor.getBrojPopunjenihSefova() << endl;
    cout << "Trezor: izbaci 0 rezultat = " << trezor.izbaciSadrzaj(0) << endl;
    cout << "Trezor: broj popunjenih = " << trezor.getBrojPopunjenihSefova() << endl;

    return 0;
}

