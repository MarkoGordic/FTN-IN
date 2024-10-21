#include <iostream>
using namespace std;

int main() {
    cout << "Unesite brojeve: ";
    
    int max = 0;
    int broj;
    do {
        cin >> broj;
        if (broj > max) {
            max = broj;
        }
    } while (broj != 0);

    cout << "Najveci uneti broj je: " << max << endl;

    return 0;
}