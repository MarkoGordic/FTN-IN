#include <iostream>
#include <iomanip>

#include "valjak.hpp"

using namespace std;



int main()
{
    cout << fixed << setprecision(2);

    Krug k1;
    Krug k2(3);
    cout << "k1: r = " << k1.getR() << ", P = " << k1.getP() << ", O = " << k1.getO() << endl;
    cout << "k2: r = " << k2.getR() << ", P = " << k2.getP() << ", O = " << k2.getO() << endl << endl;


    Pravougaonik p1;
    Pravougaonik p2(1,8);
    cout << "p1: a = "<< p1.getA() << ", b = " << p1.getB() << ", P = " << p1.getP() << ", O = " << p1.getO() << endl;
    cout << "p2: a = "<< p2.getA() << ", b = " << p2.getB() << ", P = " << p2.getP() << ", O = " << p2.getO() << endl << endl;

    Valjak v1;
    Valjak v2(2,4);
    cout << "v1: r = " << v1.getR() << ", H = "<< v1.getH() << ", P = " << v1.getP() << ", V = " << v1.getV() << endl;
    cout << "v2: r = " << v2.getR() << ", H = "<< v2.getH() << ", P = " << v2.getP() << ", V = " << v2.getV() << endl << endl;

    return 0;
}
