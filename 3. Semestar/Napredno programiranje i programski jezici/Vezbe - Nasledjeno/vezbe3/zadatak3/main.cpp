#include <iostream>

using namespace std;

#include "screen.hpp"
#include "monitor.hpp"

void printInfo(const Monitor& m){
    cout << "Monitor State: ";
    switch (m.state){
        case sON:
            cout << "ON";
            break;
        case sOFF:
            cout << "OFF";
            break;
        case sTEST:
            cout << "TEST";
            break;
        case sSTANDBY:
            cout << "STANDBY";
            break;
        case sOUT:
            cout << "OUT";
            break;
        default:
            cout << "UNKNOWN STATE";
    }
    cout << endl;
    cout << "Screen State: " << ((m.getScreenState() == ssOFF) ? "OFF": "ON") << endl;
    cout << "Brightness: " << m.getBrightness() << endl << endl;
}

void printScreen(const Screen& s1){
    cout << "Screen State: " << ((s1.getState() == ssOFF) ? "OFF": "ON") << endl;
    cout << "Brightness: " << s1.getBrightness() << endl << endl;
}

int main()
{
    Screen s1;
    cout << "TEST SCREEN" << endl;
    printScreen(s1);
    s1.setState(ssON);
    printScreen(s1);
    s1.incB();
    s1.incB();
    s1.decB();
    s1.setState(ssOFF);
    s1.incB();
    printScreen(s1);


    Monitor m1;
    cout << "TEST MONITOR" << endl;

    switch (m1.getMonitorState()){
        case sON:
            cout << "ON";
            break;
        case sOFF:
            cout << "OFF";
            break;
        case sTEST:
            cout << "TEST";
            break;
        case sSTANDBY:
            cout << "STANDBY";
            break;
        case sOUT:
            cout << "OUT";
            break;
        default:
            cout << "UNKNOWN STATE";
    }
    cout << endl;


    printInfo(m1);
    m1.turnOn();
    printInfo(m1);
    m1.turnTest();
    m1.incB();
    m1.incB();
    m1.incB();
    m1.decB();
    printInfo(m1);

    m1.turnOut();
    m1.incB();
    m1.incB();
    printInfo(m1);

    m1.turnOn();
    printInfo(m1);

    m1.repair();
    printInfo(m1);

    m1.turnOn();
    m1.turnStandBy();
    m1.decB();
    printInfo(m1);

    m1.turnOn();
    m1.decB();

    m1.turnOff();
    printInfo(m1);

    /// samo kostur za meni :)
    /*int n;
    do {
        cout << "opcije..." << endl;
        cin >> n;
        switch(n){
            case 1: s1.setState(); break;
            default: cout << "NE";
        }
        printScreen(s1);
        printInfo(m1);

    }while (n != 0);*/

    return 0;
}
