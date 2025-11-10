#include <iostream>

using namespace std;

#include "machine.hpp"

 void printInfo(const Machine& m){
    cout << "------------------------" << endl;
    cout << "Value of the machine: " << m.getValue() << endl;
    cout << "State of the machine: ";
    switch (m.getCurrentState()){
        case sA:
            cout << "sA";
            break;
        case sB:
            cout << "sB";
            break;
        case sC:
            cout << "sC";
            break;
        case sD:
            cout << "sD";
            break;
    };
    cout << endl << "------------------------" << endl;
 }

int meni() {
    int opcija = 0;
    cout << "-----------------" << endl;
    cout << "Opcija 1: metodaX" << endl;
    cout << "Opcija 2: metodaY" << endl;
    cout << "Opcija 3: metodaZ" << endl;
    cout << "Opcija 4: metodaW" << endl;
    cout << "Opcija 5: plus" << endl;
    cout << "Opcija 6: minus" << endl;
    cout << "Opcija 0: Izlaz" << endl;
    cout << "Unesite opciju: ";
    cin >> opcija;
    cout << "-----------------" << endl;
    return opcija;
}

int main()
{
    Machine m;
    /*printInfo(m);
    m.metodaX();
    printInfo(m);
    m.plus();
    printInfo(m);
    m.minus();
    printInfo(m);
    m.metodaZ();
    printInfo(m);
    m.metodaX();
    printInfo(m);
    m.metodaW();
    printInfo(m);
    m.metodaY();
    printInfo(m);
    cout << endl << endl;*/

    int opcija = 0;
    do {
        printInfo(m);
        opcija = meni();
        switch (opcija){
            case 1:
                (m.metodaX()) ? cout << "Uspesno" << endl : cout << "Nespesno" << endl;
                break;
            case 2:
                (m.metodaY()) ? cout << "Uspesno" << endl : cout << "Nespesno" << endl;
                break;
            case 3:
                (m.metodaZ()) ? cout << "Uspesno" << endl : cout << "Nespesno" << endl;
                break;
            case 4:
                (m.metodaW()) ? cout << "Uspesno" << endl : cout << "Nespesno" << endl;
                break;
            case 5:
                (m.plus()) ? cout << "Uspesno" << endl : cout << "Nespesno" << endl;
                break;
            case 6:
                (m.minus()) ? cout << "Uspesno" << endl : cout << "Nespesno" << endl;
                break;
            case 0:
                cout << "Pozdravko!" << endl;
                break;
            default:
                cout << "Nepostojeca opcija!" << endl;
        }
    }while(opcija != 0);
    return 0;
}
