#include <iostream>

using namespace std;

enum nacin_sabiranja {ISPOD, IZNAD, NA};

void unosElemenata(int n, int **pok){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cin >> pok[i][j];
        }
    }
}

void ispisElemenata(int n, int **pok){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cout << pok[i][j] << " ";
        }
        cout << endl;
    }
}

int sabirajElemente(int n, int **pok, nacin_sabiranja nacin){
    int suma = 0;
    if (nacin == NA){
        for (int i = 0; i < n; i++){
            suma += pok[i][i];
        }
    }
    if (nacin == IZNAD){
        for (int i = 1; i < n; i++){
            suma += pok[i-1][i];
        }
    }
    if (nacin == ISPOD){
        for (int i = 1; i < n; i++){
            suma += pok[i][i-1];
        }
    }

    return suma;
}

int main()
{
    int n = 0;
    cout << "Unesite dimenzije kvadratne matrice: ";
    cin >> n;
    if (n <= 0){
        cout << "Greska" << endl;
        return 1;
    }
    int** niz = new int*[n];
    if (niz == NULL){
        cout << "Greska!" << endl;
        return 1;
    }
    for (int i = 0; i < n; i++){
        niz[i] = new int[n];
        if (niz[i] == NULL){
            cout << "Greska!"<< endl;
            return 1;
        }
    }

    unosElemenata(n, niz);
    ispisElemenata(n, niz);
    cout << endl;
    cout << "NA: " << sabirajElemente(n, niz, NA) << endl;
    cout << "IZNAD: " << sabirajElemente(n, niz, IZNAD) << endl;
    cout << "ISPOD: " << sabirajElemente(n, niz, ISPOD) << endl;

    for (int i = 0; i < n; i++){
        delete []niz[i];
    }
    delete []niz;
    return 0;
}
