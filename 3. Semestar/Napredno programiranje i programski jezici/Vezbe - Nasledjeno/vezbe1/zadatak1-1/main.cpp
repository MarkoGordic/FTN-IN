#include <iostream>

using namespace std;

int main()
{
    int broj = 0, max_br = 0;
    do {
        cout << "Unesite broj: ";
        cin >> broj;
        if (broj < 0){
            cout << "Greska prilikom unosa" << endl;
            return 1;
        }
        if (broj > max_br){
            max_br = broj;
        }
    }while(broj != 0);
    cout << "Maksimalni uneseni broj: " << max_br << endl;
    return 0;
}
