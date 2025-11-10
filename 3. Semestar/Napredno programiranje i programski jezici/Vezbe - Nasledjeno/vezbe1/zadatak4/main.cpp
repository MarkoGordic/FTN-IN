#include <iostream>

using namespace std;

enum nacin_sortiranja {RASTUCE, OPADAJUCE};

void unosElemenata(int n, int *pok){
    for (int i = 0; i < n; i++){
        cin >> pok[i];
    }
}

void ispisElemenata(int n, int *pok){
    for (int i = 0; i < n; i++){
        cout << pok[i] << endl;
    }
}

void sortirajElemente(int n, int *pok, nacin_sortiranja nacin){
    for (int i = 0; i < n; i++){
        for (int j = i; j < n; j++){
            if (nacin == OPADAJUCE){
                if (pok[i] < pok[j]){
                    swap(pok[i], pok[j]);
                }
            }
            if (nacin == RASTUCE){
                if (pok[i] > pok[j]){
                    swap(pok[i], pok[j]);
                }
            }
        }
    }
}

int main()
{
    int n = 0;
    cout << "Unesite broj elemenata: ";
    cin >> n;
    if (n <= 0){
        cout << "Greska!" << endl;
        return 1;
    }
    int* niz = new int[n];
    if (niz == NULL){
        cout << "Greska!";
        return 1;
    }
    cout << endl;
    unosElemenata(n, niz);
    ispisElemenata(n, niz);
    cout << endl;
    sortirajElemente(n, niz, OPADAJUCE);
    ispisElemenata(n, niz);
    cout << endl;
    sortirajElemente(n, niz, RASTUCE);
    ispisElemenata(n, niz);
    delete []niz;
    return 0;
}
