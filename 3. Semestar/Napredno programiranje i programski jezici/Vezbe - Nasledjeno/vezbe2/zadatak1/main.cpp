#include <iostream>

using namespace std;

#include "kocka.hpp"

int meni(){
    int opcija = 0;
    cout << "Opcija 1: Baci kockicu" << endl;
    cout << "Opcija 2: Dobij vrednost kockice" << endl;
    cout << "Opcija 0: Izlaz" << endl;
    cout << "Unesite opciju: ";
    cin >> opcija;

    return opcija;
}

int main()
{
    srand(time(0));                             // rand sad zavisi od vremenskog trenutka pokretanja
                                                // na windows mora ctime da se include
    Kocka k1, k2(4), k3(k2);

    /*
    cout << k1.getVrednost() << endl;
    cout << k2.getVrednost() << endl;

    cout << "Pre bacanja: " << k3.getVrednost() << endl;
    k3.baci();
    cout << "Nakon bacanja: " << k3.getVrednost() << endl;
    */

    int opcija = 0;
    do {
        opcija = meni();
        switch (opcija){
            case 1:
                k3.baci();
                break;
            case 2:
                cout << "Vrednost kockice: " << k3.getVrednost() << endl;
                break;
            case 0:
                cout << "Pozdrav!";
                break;
            default:
                cout << "Ne postoji opcija!" << endl;
                break;
        }
        cout << endl;
    } while (opcija != 0);
    return 0;
}
