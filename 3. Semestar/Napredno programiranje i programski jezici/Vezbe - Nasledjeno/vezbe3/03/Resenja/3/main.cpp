#include <iostream>
#include "screen.hpp"
#include "monitor.hpp"
using namespace std;


#define KRAJ 13
void printScreen(Screen s){
    cout << "-- Screen --" << endl;
    cout << "Brightness: " << s.getBrightness() << endl;
    cout << "Screen state: "<< (s.getState() == ssOFF ? "OFF" : "ON") << endl;
}

void printMonitor(Monitor m){
    cout << "-- Monitor --" << endl;

    cout << "Brightness: " << m.getBrightness() << endl;
    cout << "Screen state: " << (m.getScreenState() == ssOFF ? "OFF" : "ON") << endl;

    //printScreen(m.getScreen()); //moze i ovako m.getScreen() je dodata metoda koja vraca objekat klase Screen

    cout << "Monitor state: ";
    switch (m.getMonitorState()){
        case sOUT:
            cout << "OUT";
            break;
        case sTEST:
            cout << "TEST";
            break;
        case sSTANDBY:
            cout << "STANDBY";
            break;
        case sOFF:
            cout << "OFF";
            break;
        case sON: cout << "ON";
            break;
        default:
            cout << "Nepostojece stanje";
    }
    cout << endl;
}

int meni(){

    cout << endl;
    cout << "1. Screen - Ukljuci" << endl;
    cout << "2. Screen - Iskljuci" << endl;
    cout << "3. Screen - Povecaj brightness" << endl;
    cout << "4. Screen - Smanji brightness" << endl;
    cout << "5. Monitor - Ukljuci" << endl;
    cout << "6. Monitor - Iskljuci" << endl;
    cout << "7. Monitor - Pokvari" << endl;
    cout << "8. Monitor - Popravi" << endl;
    cout << "9. Monitor - Prebaci u test" << endl;
    cout << "10. Monitor - Prebaci u standby" << endl;
    cout << "11. Monitor - Povecaj brightness" << endl;
    cout << "12. Monitor - Smanji brightness" << endl;
    cout << "13. Kraj" << endl;
    cout << "Izaberite operaciju:";
    int n;
    cin >> n;
    cout << endl << endl;
    return n;
}

int main()
{

    Screen s;
    Monitor m;

    int n;
    do {

        n = meni();

        switch (n){
            case 1: s.setState(ssON); break;
            case 2: s.setState(ssOFF); break;
            case 3: s.incB(); break;
            case 4: s.decB(); break;
            case 5: m.turnOn(); break;
            case 6: m.turnOff(); break;
            case 7: m.turnOut(); break;
            case 8: m.repair(); break;
            case 9: m.turnTest(); break;
            case 10: m.turnStandBy(); break;
            case 11: m.incB(); break;
            case 12: m.decB(); break;
            case 13: cout << "Kraj"; break;
            default: cout << "Nepostojeca operacija" << endl;
        }
        printScreen(s);
        printMonitor(m);

    } while (n != KRAJ);

    return 0;
}
