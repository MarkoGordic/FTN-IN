#include <iostream>
using namespace std;

#include "televizor.hpp"

void ispis(const Televizor& t){
    cout << "Stanje televizora: ";
    switch(t.getStanje()){
        case ISKLJUCEN:
            cout << "Iskljucen" << endl;
            break;
        case UKLJUCEN:
            cout << "Ukljucen" << endl;
            break;
        case POKVAREN:
            cout << "Pokvaren" << endl;
            break;
    }
    cout << "Zvuk: " << t.getZvuk() << endl;
    cout << "Kanal: " << t.getKanal() << endl;
}

int meni(){
    int opcija;
    do {
        cout << "1. Ukljuci televizor" << endl;
        cout << "2. Iskljuci televizor" << endl;
        cout << "3. Pokvari televizor" << endl;
        cout << "4. Popravi televizor" << endl;
        cout << "5. Pojacaj zvuk" << endl;
        cout << "6. Smanji zvuk" << endl;
        cout << "7. Sledeci kanal" << endl;
        cout << "8. Prethodni kanal" << endl;
        cout << "9. Kraj programa" << endl;
        cout << "Izaberite opciju: ";
        cin >> opcija;
    } while(opcija < 1 || opcija > 9);
    return opcija;
}

int main(){
    Televizor t;
    int opcija;

    do{
        ispis(t);
        opcija = meni();
        switch(opcija){
            case 1:
                t.ukljuci();
                break;
            case 2:
                t.iskljuci();
                break;
            case 3:
                t.pokvari();
                break;
            case 4:
                t.popravi();
                break;
            case 5:
                t.pojacajZvuk();
                break;
            case 6:
                t.smanjiZvuk();
                break;
            case 7:
                t.sledeciKanal();
                break;
            case 8:
                t.prethodniKanal();
                break;
        }
    } while(opcija != 9);

    return 0;
}