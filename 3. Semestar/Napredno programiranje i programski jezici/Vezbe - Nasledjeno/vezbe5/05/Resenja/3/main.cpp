#include "oblik.hpp"

int main()
{
    cout << "Pravougaonik p1:" << endl;
    Pravougaonik p1;
    cout << "Povrsina: " << p1.getP() << endl;
    cout << "Obim: " << p1.getO() << endl << endl;

    cout << "Pravougaonik p2:" << endl;
    Pravougaonik p2(3,5);
    cout << "Povrsina: " << p2.getP() << endl;
    cout << "Obim: " << p2.getO() << endl;
    cout << " " << endl;

    cout << "Pravougaonik p3:" << endl;
    Pravougaonik p3(p2);
    cout << "Povrsina: " << p3.getP() << endl;
    cout << "Obim: " << p3.getO() << endl << endl;


    cout << "Elipsa e1:" << endl;
    Elipsa e1;
    cout << "Povrsina: " << e1.getP() << endl;
    cout << "Obim: " << e1.getO() << endl << endl;

    cout << "Elipsa e2:" << endl;
    Elipsa e2(3,5);
    cout << "Povrsina: " << e2.getP() << endl;
    cout << "Obim: " << e2.getO() << endl << endl;

    cout << "Elipsa e3:" << endl;
    Elipsa e3(e2);
    cout << "Povrsina: " << e3.getP() << endl;
    cout << "Obim: " << e3.getO() << endl << endl;


    cout << "Kvadrat k1:" << endl;
    Kvadrat k1;
    cout << "Povrsina: " << k1.getP() << endl;
    cout << "Obim: " << k1.getO() << endl << endl;

    cout << "Kvadrat k2:" << endl;
    Kvadrat k2(4);
    cout << "Povrsina: " << k2.getP() << endl;
    cout << "Obim: " << k2.getO() << endl << endl;

    cout << "Kvadrat k3:" << endl;
    Kvadrat k3(k2);
    cout << "Povrsina: " << k3.getP() << endl;
    cout << "Obim: " << k3.getO() << endl << endl;

    cout << "Krug kr1:" << endl;
    Krug kr1;
    cout << "Povrsina: " << kr1.getP() << endl;
    cout << "Obim: " << kr1.getO() << endl << endl;

    cout << "Krug k2:" << endl;
    Krug kr2(3);
    cout << "Povrsina: " << kr2.getP() << endl;
    cout << "Obim: " << kr2.getO() << endl << endl;

    cout << "Krug k3:" << endl;
    Krug kr3(kr2);
    cout << "Povrsina: " << kr3.getP() << endl;
    cout << "Obim: " << kr3.getO() << endl << endl;


    cout << "Oblik o1:" << endl;
    Oblik o1;

    cout << "Povrsina: " << o1.getP() << endl;
    cout << "Obim: " << o1.getO() << endl << endl;

    cout << "Oblik o2:" << endl;
    Oblik o2(6);
    cout << "Povrsina: " << o2.getP() << endl;
    cout << "Obim: " << o2.getO() << endl << endl;

    cout << "Oblik o3:" << endl;
    Oblik o3(o2);
    cout << "Povrsina: " << o3.getP() << endl;
    cout << "Obim: " << o3.getO() << endl << endl;

    return 0;
}
