#include <iostream>
using namespace std;

int izracunajCenu(int br_karata, int cena_karte=50){
    return br_karata * cena_karte;
}

int main(){
    int br_karata, cena_karte;
    cout << "Unesite broj karata: ";
    cin >> br_karata;
    cout << "Unesite cenu karte: ";
    cin >> cena_karte;

    cout << "Cena karata je: " << izracunajCenu(br_karata, cena_karte) << endl;

    return 0;
}