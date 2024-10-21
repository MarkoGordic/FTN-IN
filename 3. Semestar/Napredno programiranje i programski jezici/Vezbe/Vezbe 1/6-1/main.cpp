#include <iostream>
using namespace std;

void unesiElemente(int** matrica, int dimenzija) {
    for (int i = 0; i < dimenzija; ++i) {
        for (int j = 0; j < dimenzija; ++j) {
            cout << "Unesite element [" << i << "][" << j << "]: ";
            cin >> matrica[i][j];
        }
    }
}

int sumaIznadDijagonale(int** matrica, int dimenzija) {
    int suma = 0;
    for (int i = 0; i < dimenzija; ++i) {
        for (int j = i + 1; j < dimenzija; ++j) {
            suma += matrica[i][j];
        }
    }
    return suma;
}

int sumaIspodDijagonale(int** matrica, int dimenzija) {
    int suma = 0;
    for (int i = 1; i < dimenzija; ++i) {
        for (int j = 0; j < i; ++j) {
            suma += matrica[i][j];
        }
    }
    return suma;
}

int sumaNaDijagonali(int** matrica, int dimenzija) {
    int suma = 0;
    for (int i = 0; i < dimenzija; ++i) {
        suma += matrica[i][i];
    }
    return suma;
}

int main() {
    int dimenzija;

    cout << "Unesite dimenziju kvadratne matrice: ";
    cin >> dimenzija;

    int** matrica = new int*[dimenzija];
    for (int i = 0; i < dimenzija; ++i) {
        matrica[i] = new int[dimenzija];
    }

    unesiElemente(matrica, dimenzija);

    int iznadDijagonale = sumaIznadDijagonale(matrica, dimenzija);
    int ispodDijagonale = sumaIspodDijagonale(matrica, dimenzija);
    int naDijagonali = sumaNaDijagonali(matrica, dimenzija);

    cout << "Suma elemenata iznad dijagonale: " << iznadDijagonale << endl;
    cout << "Suma elemenata ispod dijagonale: " << ispodDijagonale << endl;
    cout << "Suma elemenata na dijagonali: " << naDijagonali << endl;

    for (int i = 0; i < dimenzija; ++i) {
        delete[] matrica[i];
    }
    delete[] matrica;

    return 0;
}
