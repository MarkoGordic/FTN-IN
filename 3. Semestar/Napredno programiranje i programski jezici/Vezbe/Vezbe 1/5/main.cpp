#include <iostream>
using namespace std;

int meni(){
    int opcija;
    do {
        cout << "1. Opcija 1" << endl;
        cout << "2. Opcija 2" << endl;
        cout << "3. Opcija 3" << endl;
        cout << "4. Opcija 4" << endl;
        cout << "5. Kraj programa" << endl;
        cout << "Izaberite opciju: ";
        cin >> opcija;
    } while(opcija < 1 || opcija > 5);
    return opcija;
}

int main(){
    int opcija;

    do{
        opcija = meni();
    }while(opcija != 5);

    return 0;
}