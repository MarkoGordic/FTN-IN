#include "Machine.hpp"

int meni(){
    int ret;

    cout << "Unesite broj za zeljenu operaciju:" << endl;
    cout << "1 - X" << endl;
    cout << "2 - Y" << endl;
    cout << "3 - Z" << endl;
    cout << "4 - W" << endl;
    cout << "5 - Plus" << endl;
    cout << "6 - Minus" << endl;
    cout << "7 - Kraj rada programa" << endl;
    cout << "Operacija-> ";

    cin >> ret;
    return ret;
}

void printInfo(const Machine& m){
    cout << "Masina: ";

    cout << "STANJE - ";
    switch (m.getCurrentState()) {
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
        default:
            cout << "nedefinisano";
            break;
    }

    cout << ", VREDNOST - " << m.getValue() << endl;
}

int main()
{
    Machine m;
    int pom;

    do {
        printInfo(m);

        cout << endl;
        pom = meni();
        cout << endl;

        switch (pom) {
            case 1:
                if (m.metodaX()) {
                    cout << "Operacija je izvrsena" << endl;
                } else {
                    cout << "Operacija nije izvrsena" << endl;
                }
                break;
            case 2:
                if (m.metodaY()) {
                    cout << "Operacija je izvrsena" << endl;
                } else {
                    cout << "Operacija nije izvrsena" << endl;
                }
                break;
            case 3:
                if (m.metodaZ()) {
                    cout << "Operacija je izvrsena" << endl;
                } else {
                    cout << "Operacija nije izvrsena" << endl;
                }
                break;
            case 4:
                if (m.metodaW()) {
                    cout << "Operacija je izvrsena" << endl;
                } else {
                    cout << "Operacija nije izvrsena" << endl;
                }
                break;
            case 5 :
                if (m.plus()) {
                    cout << "Operacija je izvrsena" << endl;
                } else {
                    cout << "Operacija nije izvrsena" << endl;
                }
                break;
            case 6 :
                if (m.minus()) {
                    cout << "Operacija je izvrsena" << endl;
                } else {
                    cout << "Operacija nije izvrsena" << endl;
                }
                break;
            case 7 :
                cout << "Masina zavrsava sa radom" << endl;
                break;
            default:
                cout << "Nepostojeca operacija" << endl;
                break;
        } //switch end
        cout << endl;
    } while (pom != 7);

    return 0;
}
