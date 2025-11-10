#include <iostream>

using namespace std;

#include "screen.hpp"
#include "monitor.hpp"

void printInfo (const Monitor& m) {
    cout << "------ Monitor ------" << endl;
    cout << "Monitor state: ";
    switch (m.state) {
        case sON: cout << "ON" << endl; break;
        case sOFF: cout << "OFF" << endl; break;
        case sTEST: cout << "TEST" << endl; break;
        case sSTANDBY: cout << "STANDBY" << endl; break;
        case sOUT: cout << "OUT" << endl; break;
    }
    cout << endl << "Screen state: ";
    switch (m.getScreenState()) {
        case ssON: cout << "ON" << endl; break;
        case ssOFF: cout << "OFF" << endl; break;
    }
    cout << endl << "Brightness: " << m.getBrightness() << endl;
    cout << "---------------------" << endl << endl;
}

int main()
{
    Screen s1;

    s1.setState(ssON);

    s1.incB();
    s1.incB();
    s1.incB();
    s1.decB();

    cout << s1.getBrightness() << " " << ((s1.getState() == ssON) ? "ON" : "OFF") << endl;

    Monitor m1;
    printInfo(m1);

    m1.turnOn();
    printInfo(m1);

    m1.turnTest();
    printInfo(m1);

    m1.turnOut();
    printInfo(m1);

    m1.repair();
    printInfo(m1);

    m1.turnOn();
    printInfo(m1);

    m1.turnStandBy();
    printInfo(m1);

    m1.turnOn();
    printInfo(m1);

    m1.incB();
    m1.incB();
    m1.incB();
    m1.decB();

    printInfo(m1);

    cout << m1.getBrightness() << " " << ((m1.getScreenState() == ssON) ? "ON" : "OFF") << endl;
    switch (m1.getMonitorState()) {
        case sON: cout << "ON" << endl; break;
        case sOFF: cout << "OFF" << endl; break;
        case sTEST: cout << "TEST" << endl; break;
        case sSTANDBY: cout << "STANDBY" << endl; break;
        case sOUT: cout << "OUT" << endl; break;
    }
    cout << endl;

    return 0;
}
