#include <iostream>
#include <ctime>
#include "Lovac.hpp"
#include "Duh.hpp"
#include "UkletaKuca.hpp"
#include "Svetionik.hpp"
#include "LovNaDuhove.hpp"

using namespace std;

int main() {
    srand(time(0));

    Lovac lovac;

    Duh duh1(rand() % 21);
    Duh duh2(rand() % 21);
    Duh duh3(rand() % 21);
    UkletaKuca ukletaKuca(duh1, duh2, duh3);

    Duh duhSvetionik(rand() % 21);
    Svetionik svetionik(duhSvetionik);

    LovNaDuhove igra(lovac, ukletaKuca, svetionik);

    bool igraUToku = true;
    while (igraUToku) {
        cout << "\n--- Lov na duhove ---\n";
        cout << "1. Zapocni lov\n";
        cout << "2. Ispisi situaciju\n";
        cout << "3. Izlaz iz igre\n";
        cout << "Izaberite opciju: ";

        int izbor;
        cin >> izbor;

        switch (izbor) {
            case 1:
                igra.zapocniLov();
                break;
            case 2:
                igra.ispisi();
                break;
            case 3:
                cout << "Izlazak iz igre...\n";
                igraUToku = false;
                break;
            default:
                cout << "Nevalidan izbor. Pokusajte ponovo.\n";
        }
    }

    return 0;
}
