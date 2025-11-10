#include <iostream>

using namespace std;

#include "dinstring.hpp"
#include "niz.hpp"

int main()
{
    Niz <int, 10> n1;
    n1.ispisi();

    n1.Unesi(10, 0);
    n1.Unesi(20, 1);
    n1.Unesi(30, 5);
    n1.Unesi(40, 5);

    n1.ispisi();

    cout << endl;

    Niz <DinString, 20> n2;
    n2.ispisi();

    n2.Unesi("Mjau", 0);
    n2.Unesi("Mjau", 1);
    n2.Unesi("Mjau", 5);
    n2.Unesi("Crnjo", 5);

    n2.ispisi();
    return 0;
}
