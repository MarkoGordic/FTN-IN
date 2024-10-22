#include <iostream>
using namespace std;

#include "monitor.hpp"

void printInfo(const Monitor& m){
    cout << "Monitor state: ";
    switch(m.getMonitorState()){
        case sON:
            cout << "ON" << endl;
            break;
        case sOFF:
            cout << "OFF" << endl;
            break;
        case sOUT:
            cout << "OUT" << endl;
            break;
        case sTEST:
            cout << "TEST" << endl;
            break;
        case sSTANDBY:
            cout << "STANDBY" << endl;
            break;
    }

    cout << "Screen state: ";
    switch(m.getScreenState()){
        case ssON:
            cout << "ON" << endl;
            break;
        case ssOFF:
            cout << "OFF" << endl;
            break;
    }

    cout << "Brightness: " << m.getBrightness() << endl;
}

int menu(){
    int opcija;
    cout << "1. Turn on" << endl;
    cout << "2. Turn off" << endl;
    cout << "3. Turn out" << endl;
    cout << "4. Turn test" << endl;
    cout << "5. Turn standby" << endl;
    cout << "6. Repair" << endl;
    cout << "7. Increase brightness" << endl;
    cout << "8. Decrease brightness" << endl;
    cout << "9. Exit" << endl;
    cout << "Option: ";
    cin >> opcija;
    return opcija;
}

int main(){
    Monitor m;
    int opcija;

    do{
        printInfo(m);
        opcija = menu();

        switch(opcija){
            case 1:
                if(m.turnOn()){
                    cout << "Monitor je upaljen" << endl;
                }else{
                    cout << "Ne mozete upaliti monitor" << endl;
                }
                break;
            case 2:
                if(m.turnOff()){
                    cout << "Monitor je ugasen" << endl;
                }else{
                    cout << "Ne mozete ugasiti monitor" << endl;
                }
                break;
            case 3:
                if(m.turnOut()){
                    cout << "Monitor je izasao iz upotrebe" << endl;
                }else{
                    cout << "Ne mozete izbaciti monitor iz upotrebe" << endl;
                }
                break;
            case 4:
                if(m.turnTest()){
                    cout << "Monitor je u test modu" << endl;
                }else{
                    cout << "Ne mozete staviti monitor u test mod" << endl;
                }
                break;
            case 5:
                if(m.turnStandby()){
                    cout << "Monitor je u standby modu" << endl;
                }else{
                    cout << "Ne mozete staviti monitor u standby mod" << endl;
                }
                break;
            case 6:
                if(m.repair()){
                    cout << "Monitor je popravljen" << endl;
                }else{
                    cout << "Ne mozete popraviti monitor" << endl;
                }
                break;
            case 7:
                if(m.incB()){
                    cout << "Brightness je povecan" << endl;
                }else{
                    cout << "Ne mozete povecati brightness" << endl;
                }
                break;
            case 8:
                if(m.decB()){
                    cout << "Brightness je smanjen" << endl;
                }else{
                    cout << "Ne mozete smanjiti brightness" << endl;
                }
                break;
            case 9:
                cout << "Izlaz" << endl;
                break;
            default:
                cout << "Nepostojeca opcija" << endl;
                break;
        }
    }while(opcija != 9);

    return 0;
}