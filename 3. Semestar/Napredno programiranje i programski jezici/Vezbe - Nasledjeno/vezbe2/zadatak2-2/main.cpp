#include <iostream>

using namespace std;

#include "televizor.hpp"

void ispis(const Televizor &t){
    cout << "Stanje: ";
    switch(t.getStanje()){
    case UKLJUCEN:
        cout << "UKLJUCEN";
        break;
    case ISKLJUCEN:
        cout << "ISKLJUCEN";
        break;
    case POKVAREN:
        cout << "POKVAREN";
        break;
    }
    cout << endl;
    cout << "Kanal: " << t.getKanal() << endl;
    cout << "Zvuk: " << t.getZvuk() << endl;
}

int meni (){
    cout << "Opcija 1: Ukljuci" << endl;
    cout << "Opcija 2: Iskljuci" << endl;
    cout << "Opcija 3: Pokvari" << endl;
    cout << "Opcija 4: Popravi" << endl;
    cout << "Opcija 5: zvuk++" << endl;
    cout << "Opcija 6: zvuk--" << endl;
    cout << "Opcija 7: kanal++" << endl;
    cout << "Opcija 8: kanal--" << endl;
    cout << "Opcija 0: Izlaz" << endl;
    int opcija = 0;
    cout << "Opcija: ";
    cin >> opcija;
    return opcija;
}

int main()
{
    Televizor t1;
    Televizor t2(t1);
    int opcija = 0;
    do {
        ispis(t1);
        opcija = meni();
        switch (opcija){
        case 1:
            (t1.ukljuci()) ? cout << "Uspesno" : cout << "Neuspesno";
            break;
        case 2:
            (t1.iskljuci()) ? cout << "Uspesno" : cout << "Neuspesno";
            break;
        case 3:
            (t1.pokvari()) ? cout << "Uspesno" : cout << "Neuspesno";
            break;
        case 4:
            (t1.popravi()) ? cout << "Uspesno" : cout << "Neuspesno";
            break;
        case 5:
            (t1.pojacajZvuk()) ? cout << "Uspesno" : cout << "Neuspesno";
            break;
        case 6:
            (t1.smanjiZvuk()) ? cout << "Uspesno" : cout << "Neuspesno";
            break;
        case 7:
            (t1.sledeciKanal()) ? cout << "Uspesno" : cout << "Neuspesno";
            break;
        case 8:
            (t1.prethodniKanal()) ? cout << "Uspesno" : cout << "Neuspesno";
            break;
        case 0:
            cout << "Pozdravko!";
            break;
        default:
            cout << "Ne postoji opcija!";
        }
        cout << endl;
    }while (opcija != 0);
    return 0;
}
