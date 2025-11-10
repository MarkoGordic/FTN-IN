#include <iostream>

using namespace std;

#include "krug.hpp"
#include "pravougaonik.hpp"
#include "valjak.hpp"

int main()
{
    // ispravno testirana klasa Krug
    Krug k1, k2(3);

    cout << "krug k1" << endl;
    cout << "r: "<< k1.getR() << endl;
    cout << "O: " << k1.getO() << endl;
    cout << "P: " << k1.getP() << endl;

    // valjda ispravno testirana klasa Pravougaonik
    Pravougaonik p1, p2(2), p3(3, 4);
    cout << "pravougaonik p1" << endl;
    cout << "a: "<< p1.getA() << endl;
    cout << "b: "<< p1.getB() << endl;
    cout << "O: " << p1.getO() << endl;
    cout << "P: " << p1.getP() << endl;

    cout << "pravougaonik p2" << endl;
    cout << "a: "<< p2.getA() << endl;
    cout << "b: "<< p2.getB() << endl;
    cout << "O: " << p2.getO() << endl;
    cout << "P: " << p2.getP() << endl;

    cout << "pravougaonik p3" << endl;
    cout << "a: "<< p3.getA() << endl;
    cout << "b: "<< p3.getB() << endl;
    cout << "O: " << p3.getO() << endl;
    cout << "P: " << p3.getP() << endl;

    // valjak vreme
    Valjak v1, v2(2), v3(3, 4);
    cout << "valjak v1" << endl;
    cout << "r: "<< v1.getR() << endl;
    cout << "H: "<< v1.getH() << endl;
    cout << "P: " << v1.getP() << endl;
    cout << "V: " << v1.getV() << endl;
    return 0;
}
