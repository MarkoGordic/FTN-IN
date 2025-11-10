#include "rerna.hpp"


void ispisiRernu(const Rerna &r) {
    cout << "Rerna: ";

    cout << "STANJE - ";
    switch (r.getTrenutnoStanje()) {
        case UKLJUCENA:
            cout << "ukljucena";
            break;
        case ISKLJUCENA:
            cout << "iskljucena";
            break;
        case POKVARENA:
            cout << "pokvarena";
            break;
        default:
            cout << "nedefinisano";
            break;
    }

    cout << ", TEMP - " << r.getTemperatura() << endl;
}


int meni() {
    int i;

    cout << "Izaberite operaciju" << endl;
    cout << "1. Ukljuci rernu" << endl;
    cout << "2. Iskljuci rernu" << endl;
    cout << "3. Pokvari rernu" << endl;
    cout << "4. Popravi rernu" << endl;
    cout << "5. Pojacaj temperaturu" << endl;
    cout << "6. Smanji temperaturu" << endl;
    cout << "7. Prikazi stanje" << endl;
    cout << "8. Kraj rada programa" << endl;
    cout << "Operacija-> ";

    cin >> i;

    return i;
}

int main()
{
    int i;
    Rerna r;

    do {
        cout << endl;
        i = meni();

        cout << endl;
        switch(i) {
            case 1:
                if (r.ukljuci()) {
                    cout << "Operacija je izvrsena" << endl;
                } else {
                    cout << "Operacija nije izvrsena" << endl;
                }
                break;
            case 2:
                if (r.iskljuci()) {
                    cout << "Operacija je izvrsena" << endl;
                } else {
                    cout << "Operacija nije izvrsena" << endl;
                }
                break;
            case 3:
                if (r.pokvari()) {
                    cout << "Operacija je izvrsena" << endl;
                } else {
                    cout << "Operacija nije izvrsena" << endl;
                }
                break;
            case 4:
                if (r.popravi()) {
                    cout << "Operacija je izvrsena" << endl;
                } else {
                    cout << "Operacija nije izvrsena" << endl;
                }
                break;
            case 5:
                if (r.pojacajTemperaturu()) {
                    cout << "Operacija je izvrsena" << endl;
                } else {
                    cout << "Operacija nije izvrsena" << endl;
                }
                break;
            case 6:
                if (r.smanjiTemperaturu()) {
                    cout << "Operacija je izvrsena" << endl;
                } else {
                    cout << "Operacija nije izvrsena" << endl;
                }
                break;
            case 7:
                //Umesto, ili pored, opcije 7 u meniju, moze se realizovati tako da se uradi ispis posle svake operacije
                ispisiRernu(r);
                break;
            case 8:
                cout << "Kraj koriscenja rerne" << endl;
                break;
            default:
                cout << "Nepostojeca operacija" << endl;
                break;
        }
    } while (i != 8);

    return 0;
}
