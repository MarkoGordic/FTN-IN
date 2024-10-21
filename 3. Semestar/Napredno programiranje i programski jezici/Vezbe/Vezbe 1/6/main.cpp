#include <iostream>
#include <algorithm>
using namespace std;

enum Sortiranje { RASTUCE, OPADAJUCE };

void unesiElemente(int* niz, int duzina) {
    for (int i = 0; i < duzina; ++i) {
        cout << "Unesite element " << i + 1 << ": ";
        cin >> niz[i];
    }
}

void sortirajNiz(int* niz, int duzina, Sortiranje vrstaSortiranja) {
    if (vrstaSortiranja == RASTUCE) {
        std::sort(niz, niz + duzina);
    } else if (vrstaSortiranja == OPADAJUCE) {
        std::sort(niz, niz + duzina, greater<int>());
    }
}

void stampajElemente(int* niz, int duzina) {
    cout << "Elementi niza su: ";
    for (int i = 0; i < duzina; ++i) {
        cout << niz[i] << " ";
    }
    cout << endl;
}

int main() {
    int duzina;
    cout << "Unesite duzinu niza: ";
    cin >> duzina;

    int* niz = new int[duzina];
    unesiElemente(niz, duzina);

    int izbor;
    cout << "Unesite vrstu sortiranja (0 za RASTUCE, 1 za OPADAJUCE): ";
    cin >> izbor;

    sortirajNiz(niz, duzina, static_cast<Sortiranje>(izbor));
    stampajElemente(niz, duzina);

    delete[] niz;

    return 0;
}
