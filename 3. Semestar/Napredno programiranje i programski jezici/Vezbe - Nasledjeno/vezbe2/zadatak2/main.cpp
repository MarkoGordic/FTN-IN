#include <iostream>

using namespace std;

#include "rerna.hpp"

int meni(){
    int opcija = 0;
    cout << "Opcija 1: Ukljuci rernu" << endl;
    cout << "Opcija 2: Iskljuci rernu" << endl;
    cout << "Opcija 3: Pokvari rernu" << endl;
    cout << "Opcija 4: Popravi rernu" << endl;

    cout << "Opcija 5: Pojacaj temperaturu rerne" << endl;
    cout << "Opcija 6: Smanji temperaturu rerne" << endl;

    cout << "Opcija 7: Ispisi rernu" << endl;

    cout << "Opcija 0: Izlaz" << endl;
    cout << "Unesite opciju: ";
    cin >> opcija;

    return opcija;
}

void ispisiRernu(const Rerna& r){
    cout << "Trenutno stanje: ";
    switch(r.getTrenutnoStanje()){
        case UKLJUCENA:
            cout << "UKLJUCENA" << endl;
            break;
        case ISKLJUCENA:
            cout << "ISKLJUCENA" << endl;
            break;
        case POKVARENA:
            cout << "POKVARENA" << endl;
            break;
    }
    cout << "Temperatura: " << r.getTemperatura() << endl;
}

int main()
{
    Rerna r;
    /*r.ukljuci();
    r.iskljuci();
    r.pokvari();
    r.popravi();
    r.pojacajTemperaturu();
    r.smanjiTemperaturu();
    r.getTemperatura();
    r.getTrenutnoStanje();
    ispisiRernu(r);*/

    int opcija = 0;
    do {
        opcija = meni();
        switch (opcija){
            case 1: {
                if (r.ukljuci()){
                    cout << "Uspesno!" << endl;
                }
                else {
                    cout << "Neuspesno!" << endl;
                }
                break;
            }
            case 2: {
                if (r.iskljuci()){
                    cout << "Uspesno!" << endl;
                }
                else {
                    cout << "Neuspesno!" << endl;
                }
                break;
            }
            case 3: {
                if (r.pokvari()){
                    cout << "Uspesno!" << endl;
                }
                else {
                    cout << "Neuspesno!" << endl;
                }
                break;
            }
            case 4: {
                if (r.popravi()){
                    cout << "Uspesno!" << endl;
                }
                else {
                    cout << "Neuspesno!" << endl;
                }
                break;
            }
            case 5: {
                if (r.pojacajTemperaturu()){
                    cout << "Uspesno!" << endl;
                }
                else {
                    cout << "Neuspesno!" << endl;
                }
                break;
            }
            case 6: {
                if (r.smanjiTemperaturu()){
                    cout << "Uspesno!" << endl;
                }
                else {
                    cout << "Neuspesno!" << endl;
                }
                break;
            }
            case 7: {
                ispisiRernu(r);
                break;
            }
            case 0: {
                cout << "Pozdrav!";
                break;
            }
            default:
                cout << "Ne postoji opcija!" << endl;
                break;
        }
        cout << endl;
    } while (opcija != 0);

    return 0;
}
