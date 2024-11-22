#include <iostream>

using namespace std;

#include "Trezor.hpp"
#include "Dijamant.hpp"

int main() {
    Trezor<Dijamant, 5> trezor;
    Dijamant d1(2, 3);
    Dijamant d2(5, 6);
    Dijamant d3(8, 9);

    trezor.ubaciSadrzaj(d1);
    trezor.ubaciSadrzaj(d2);

    cout << "Broj popunjenih sefova: " << trezor.getBrojPopunjenihSefova() << endl;

    return 0;
}