#include <iostream>
using namespace std;

int main() {
    cout << "Unesite koliko brojeva zelite da saberete: ";
    
    int n;
    int suma = 0;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int broj;
        cout << "Unesite " << i + 1 << ". broj: ";
        cin >> broj;
        suma += broj;
    }

    cout << "Suma unetih brojeva je: " << suma << endl;

    return 0;
}