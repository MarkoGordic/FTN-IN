#include <iostream>
using namespace std;

#include <kocka.hpp>

int meni(){
    int izbor;
    cout << "1. Baci kocku" << endl;
    cout << "2. Prikazi vrednost kocke" << endl;
    cout << "3. Izadji" << endl;
    cout << "Izbor: ";
    cin >> izbor;
    return izbor;
}

int main() {
    srand(time(0));

    Kocka k;
    cout << "Vrednost kocke k je: " << k.getVrednost() << endl;
    
    Kocka k2(3);
    k.baci();
    cout << "Vrednost kocke k je: " << k.getVrednost() << endl;
    k.baci();
    cout << "Vrednost kocke k je: " << k.getVrednost() << endl;

    Kocka k3(k);
    cout << "Vrednost kocke k3 je: " << k3.getVrednost() << endl;

    int izbor;
    do{
        izbor = meni();
        switch(izbor){
            case 1:
                k.baci();
                break;
            case 2:
                cout << "Vrednost kocke k je: " << k.getVrednost() << endl;
                break;
            case 3:
                cout << "Izlaz iz programa" << endl;
                break;
            default:
                cout << "Nepostojeca opcija" << endl;
        }
    }while(izbor != 3);

    return 0;
}