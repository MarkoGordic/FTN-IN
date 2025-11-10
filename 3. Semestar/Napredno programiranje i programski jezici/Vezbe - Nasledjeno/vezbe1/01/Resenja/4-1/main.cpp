#include <iostream>
using namespace std;

enum PozicijaElemenata {IZNAD_DIJAGONALE, ISPOD_DIJAGONALE, DIJAGONALA};

void unosElemenata(int** matrica, int dimenzija) {
    cout << "Unos elemenata matrice" << endl;

    for(int i = 0; i < dimenzija; i++){
        for(int j = 0; j < dimenzija; j++){
            cout << "\tmatrica[" << i << "][" << j << "] = ";
            cin >> matrica[i][j];
        }
    }
    cout << endl;
}

int suma(int** matrica, int dimenzija, PozicijaElemenata pozicija){
    int suma = 0;

    switch(pozicija){
        // kada se radi sa matricom mogu se uociti neke zakonitosti
        // na primer:
        // KOLONA   0  1  2  3    INDEKSI ELEMENATA     INDEKSI SA VREDNOSTIMA
        //        ------------    ------------------    ----------------------
        //  RED 0:  1  2  3  4      00 01 02 03         00= 1 01= 2 02= 3  03= 4
        //  RED 1:  5  6  7  8      10 11 12 13         10= 5 11= 6 12= 7  13= 8
        //  RED 2:  9 10 11 12      20 21 22 23         20= 9 21=10 22=11  23=12
        //  RED 3: 13 14 15 16      30 31 32 33         30=13 31=14 32=15  33=16
        //
        // elementi iznad glavne dijagonale (01, 02, 03, 12, 13, 23) - indeksa reda je uvek manji od indeksa kolone
        // elementi glavne dijagonale - (00, 11, 22, 33) - indeksa reda je jednak indeksu kolone
        // elementi ispod glavne dijagonale - (10, 20, 21, 30, 31, 32) - indeks reda je uvek veci od indeksa kolone

        case IZNAD_DIJAGONALE:
            for(int i = 0; i < dimenzija; i++){
                for(int j = 0; j < dimenzija; j++){
                    if(i < j){
                        suma += matrica[i][j];
                    }
                }
            }
            break;
        case DIJAGONALA:
            for(int i = 0; i < dimenzija; i++){
                for(int j = 0; j < dimenzija; j++){
                    if(i == j){
                        suma += matrica[i][j];
                    }
                }
            }
            break;
        case ISPOD_DIJAGONALE:
            for(int i = 0; i < dimenzija; i++){
                for(int j = 0; j < dimenzija; j++){
                    if(i > j){
                        suma += matrica[i][j];
                    }
                }
            }
            break;
    }
    return suma;
}


int main()
{
    int n;
    int **matrica;

    cout << "Dimenzija matrice: ";
    cin >> n;
    cout << endl;

    if (n <= 0) {
        cout << "Greska: Dimenzija mora biti pozitivan broj" << endl;
        return 0;
    }

    // rezervacija memorije za 1. dimenziju
    matrica = new int*[n];

    if(matrica == NULL){
        cout << "Greska: Racunar nema dovoljno memorije" << endl;
        return 0;
    }

    for(int i = 0; i < n; i++){
        // rezervacija memorije za 2. dimenziju
        matrica[i] = new int[n];
        if(matrica[i] == NULL){
            cout << "Greska: Racunar nema dovoljno memorije" << endl;
            return 0;
        }
    }

    unosElemenata(matrica, n);

    cout << "Suma elemenata iznad glavne dijagonale: " << suma(matrica, n, IZNAD_DIJAGONALE) << endl;
    cout << "Suma elemenata glavne dijagonale: " << suma(matrica, n, DIJAGONALA) << endl;
    cout << "Suma elemenata ispod glavne dijagonale: " << suma(matrica, n, ISPOD_DIJAGONALE) << endl;

    // oslobadjanje dinamicki alocirane memorije
    for(int i = 0; i < n; i++){
        delete[] matrica[i];
    }
    delete[] matrica;

    return 0;
}

