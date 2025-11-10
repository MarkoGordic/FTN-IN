#include <iostream>

using namespace std;
#include "zicara.hpp"
#include "dete.hpp"

int main()
{
    cout<<"Testiranje klase Karta: "<<endl<<endl;

    Karta k1, k2(2, SKI);
    cout << k1.getBrojKarte() << endl;
    cout << k1.getVrstaKarte() << endl;

    cout << k1 << endl;
    cout << k2 << endl;

    cout<<"-------------------------------------------------------"<<endl;
    cout<<"Testiranje klase Putnik: "<<endl<<endl;
    Putnik p1, p2(3, SKI_OPENING, "1234567891012", "Dusan Tadic");
    cout << p2.getMb() << endl;
    cout << p2.getVrstaKarte() << endl;
    cout << p2.toString() << endl << endl;

    cout << p1 << endl;
    cout << p2 << endl;

    Putnik p3(5, LETO, "546843113154", "C Ronaldo");

    cout<<"-------------------------------------------------------"<<endl;
    cout<<"Testiranje klase PutnikDete: "<<endl<<endl;
    PutnikDete pd1, pd2(4, SKI, "464643216877", "Neymar", "1234567891012"), pd3(p3, "2222222222221");
    cout << pd2.toString() << endl;

    cout<<"-------------------------------------------------------"<<endl;
    cout<<"Testiranje klase Zicara: "<<endl<<endl;
    Zicara<LETO, 2, 1> zicara;
    cout << zicara << endl;

    zicara.otvori();
    cout << zicara << endl;

    zicara.dodajPutnika(&p1);
    zicara.dodajPutnika(&p2);
    zicara.dodajPutnika(&p3);
    zicara.dodajPutnika(&pd1);
    zicara.dodajPutnika(&pd2);
    zicara.dodajPutnika(&pd3);

    cout << zicara << endl;

    zicara.preveziTuru();
    cout << zicara << endl;

    zicara.zatvori();
    cout << zicara << endl;

    return 0;
}
