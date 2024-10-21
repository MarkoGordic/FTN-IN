#include <iostream>
using namespace std;

#include "rerna.hpp"

void ispisiRernu(const Rerna& r){
    cout << "Temperatura: " << r.getTemperatura() << endl;
    cout << "Stanje rerne: ";
    switch(r.getTrenutnoStanje()){
        case ISKLJUCENA:
            cout << "Iskljucena" << endl;
            break;
        case UKLJUCENA:
            cout << "Ukljucena" << endl;
            break;
        case POKVARENA:
            cout << "Pokvarena" << endl;
            break;
    }
}

int meni(){
    int opcija;
    do {
        cout << "1. Ukljuci rernu" << endl;
        cout << "2. Iskljuci rernu" << endl;
        cout << "3. Pokvari rernu" << endl;
        cout << "4. Popravi rernu" << endl;
        cout << "5. Pojacaj temperaturu" << endl;
        cout << "6. Smanji temperaturu" << endl;
        cout << "7. Kraj programa" << endl;
        cout << "Izaberite opciju: ";
        cin >> opcija;
    } while(opcija < 1 || opcija > 7);
    return opcija;
}

int main(){
    Rerna r;
    int opcija;

    do{
        ispisiRernu(r);
        opcija = meni();
        switch(opcija){
            case 1:
                r.ukljuci();
                break;
            case 2:
                r.iskljuci();
                break;
            case 3:
                r.pokvari();
                break;
            case 4:
                r.popravi();
                break;
            case 5:
                r.pojacajTemperaturu();
                break;
            case 6:
                r.smanjiTemperaturu();
                break;
        }
    }while(opcija != 7);

    return 0;
}