#include "artikal.hpp"

int main()
{
    Artikal a1("Milka sa lesnikom 150gr", 142.23);
    cout << a1 << endl;

    DinString d1("Next jabuka 1l");

    Artikal a2(d1, 110);
    cout << a2 << endl;

    // uloga destruktora:
    // kreira se treci objekat
    {
        Artikal a3(a2);
        cout << a3 << endl;
    }
    // unisten je treci objekat

    cout << a2 << endl;

    return 0;
}
