#include <iostream>
using namespace std;

#include "machine.hpp"

int meni() {
    int izbor;
    cout << "1. Metoda X" << endl;
    cout << "2. Metoda Y" << endl;
    cout << "3. Metoda Z" << endl;
    cout << "4. Metoda W" << endl;
    cout << "5. Plus" << endl;
    cout << "6. Minus" << endl;
    cout << "7. Kraj" << endl;
    cout << "Izbor: ";
    cin >> izbor;
    return izbor;
}

void printInfo(const Machine& m) {
    cout << "Vrednost: " << m.getValue() << endl;
    MachineState tren = m.getCurrentState();

    cout << "Stanje: ";
    switch (tren)
    {
        case sA:
            cout << "sA" << endl;
            break;
        case sB:
            cout << "sB" << endl;
            break;
        case sC:
            cout << "sC" << endl;
            break;
        case sD:
            cout << "sD" << endl;
    }
}

int main() {
    Machine m;

    int izbor;
    do{
        izbor = meni();
        switch (izbor)
        {
            case 1:
                if(m.metodaX())
                    cout << "Metoda X uspesno izvrsena" << endl;
                else
                    cout << "Metoda X nije uspesno izvrsena" << endl;
                break;
            case 2:
                if(m.metodaY())
                    cout << "Metoda Y uspesno izvrsena" << endl;
                else
                    cout << "Metoda Y nije uspesno izvrsena" << endl;
                break;
            case 3:
                if(m.metodaZ())
                    cout << "Metoda Z uspesno izvrsena" << endl;
                else
                    cout << "Metoda Z nije uspesno izvrsena" << endl;
                break;
            case 4:
                if(m.metodaW())
                    cout << "Metoda W uspesno izvrsena" << endl;
                else
                    cout << "Metoda W nije uspesno izvrsena" << endl;
                break;
            case 5:
                if(m.plus())
                    cout << "Plus uspesno izvrsen" << endl;
                else
                    cout << "Plus nije uspesno izvrsen" << endl;
                break;
            case 6:
                if(m.minus())
                    cout << "Minus uspesno izvrsen" << endl;
                else
                    cout << "Minus nije uspesno izvrsen" << endl;
                break;
            case 7:
                cout << "Kraj" << endl;
                break;
            default:
                cout << "Nepostojeca opcija" << endl;
        }
        printInfo(m);
    }while(izbor != 7);

    return 0;
}