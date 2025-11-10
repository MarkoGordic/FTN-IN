#include <iostream>

// Komentari po klasama su Marijini :)

using namespace std;

#include "trougao.hpp"
#include "jktrougao.hpp"
#include "jstrougao.hpp"

int main()
{
    Trougao t1, t2(4, 5, 6), t3(t2);

    t1.setA(5);
    t1.setB(6);
    t1.setC(7);

    cout << t1.getO() << endl;
    cout << t1.getP() << endl;
    cout << t1.getA() << endl;
    cout << t1.getB() << endl;
    cout << t1.getC() << endl;

    JKTrougao jk1, jk2(2, 3), jk3(jk2);

    jk1.setA(4);
    jk1.setB(3);
    jk1.setC(3);

    cout << jk1.getO() << endl;
    cout << jk1.getP() << endl;

    JSTrougao js1, js2(2), js3(js2);

    js1.setA(4);
    js1.setB(4);
    js1.setC(4);

    cout << js1.getO() << endl;
    cout << js1.getP() << endl;


    return 0;
}
