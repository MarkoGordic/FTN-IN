#include "pravilanOblik.hpp"

int main()
{
    Pravougaonik p0, p1(8, 4), p2(p1);

    cout << "*** Pravougaonik ***" << endl << endl;
    cout << "p0 -> (" << p0.getA() << ", " << p0.getB() << ") => P = " << p0.getP() << ", O = " << p0.getO() << endl;
    cout << "p1 -> (" << p1.getA() << ", " << p1.getB() << ") => P = " << p1.getP() << ", O = " << p1.getO() << endl;
    cout << "p2 -> (" << p2.getA() << ", " << p2.getB() << ") => P = " << p2.getP() << ", O = " << p2.getO() << endl << endl;

    Elipsa e0, e1(4, 2), e2(e1);

    cout << "*** Elipsa ***" << endl << endl;
    cout << "e0 -> (" << e0.getX() << ", " << e0.getY() << ") => P = " << e0.getP() << ", O = " << e0.getO() << endl;
    cout << "e1 -> (" << e1.getX() << ", " << e1.getY() << ") => P = " << e1.getP() << ", O = " << e1.getO() << endl;
    cout << "e2 -> (" << e2.getX() << ", " << e2.getY() << ") => P = " << e2.getP() << ", O = " << e2.getO() << endl << endl;

    Oblik o0, o1(8, 4), o2(o1);

    cout << "*** Oblik ***" << endl << endl;
    cout << "o0 -> P = " << o0.getP() << ", O = " << o0.getO() << endl;
    cout << "o1 -> P = " << o1.getP() << ", O = " << o1.getO() << endl;
    cout << "o2 -> P = " << o2.getP() << ", O = " << o2.getO() << endl << endl;

    PravilanOblik po0, po1(6), po2(po1);

    cout << "*** Pravilan oblik ***" << endl << endl;
    cout << "po0 -> P = " << po0.getP() << ", O = " << po0.getO() << endl;
    cout << "po1 -> P = " << po1.getP() << ", O = " << po1.getO() << endl;
    cout << "po2 -> P = " << po2.getP() << ", O = " << po2.getO() << endl << endl;

    return 0;
}
