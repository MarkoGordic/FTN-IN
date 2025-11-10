#include <iostream>
using namespace std;

double ukupnaCena(int kolicina, double cena = 50){
    return kolicina * cena;
}

int main()
{
    int brojKarata;
    double cenaKarte, potrebanNovac;

    cout << "Koliko karata biste da kupite: ";
    cin >> brojKarata;
    cout << endl;

    if (brojKarata <= 0) {
        cout << "Greska: Broj karata mora biti pozitivan broj";
        return 0;
    }

    cout << "Unesite cenu jedne karte.\nUkoliko zelite da koristite podrazumevanu cenu unesite negativan broj: ";
    cin >> cenaKarte;
    cout << endl;

    if(cenaKarte < 0){
        potrebanNovac = ukupnaCena(brojKarata);
    } else {
        potrebanNovac = ukupnaCena(brojKarata, cenaKarte);
    }

    cout << "Vas racun iznosi " << potrebanNovac << " dinara." << endl;

    return 0;
}
