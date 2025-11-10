#include <iostream>

using namespace std;

#include "dinstring.hpp"
#include "trezor.hpp"
#include "dijamant.hpp"

int main()
{
    Dijamant d1, d2(3, 0.02), d3(d2);
    cout << d2 << endl;

    Trezor<Dijamant, 2> trezor;
    cout << trezor << endl;
    trezor.ubaciSadrzaj(d2);
    trezor.ubaciSadrzaj(d2);
    trezor.ubaciSadrzaj(d1);
    cout << trezor << endl;
    trezor.izbaciSadrzaj(1);
    cout << trezor << endl;
    cout << trezor.getBrojPopunjenihSefova() << endl;
    return 0;
}
