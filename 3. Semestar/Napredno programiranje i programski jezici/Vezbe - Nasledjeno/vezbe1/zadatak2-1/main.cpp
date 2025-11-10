#include <iostream>

using namespace std;

int cena_karata(int broj_karata, int cena_karte = 50){
    if (broj_karata <= 0){
        return -1;
    }
    return broj_karata * cena_karte;
}

int main()
{
    int cena_karte = 0, broj_karata = 0;
    cout << "Unesite broj karata: ";
    cin >> broj_karata;
    if (broj_karata <= 0){
        cout << "Greska"<< endl;
        return 1;
    }
    cout << "Unesite cenu karte: ";
    cin >> cena_karte;
    int ukupno = 0;
    if (cena_karte <= 0){
        ukupno = cena_karata(broj_karata);
    }
    else {
        ukupno = cena_karata(broj_karata, cena_karte);
    }
    if (ukupno == -1){
        cout << "Greska!";
        return 1;
    }
    cout << "Potrebno je " << ukupno << " dinara" << endl;
    return 0;
}
