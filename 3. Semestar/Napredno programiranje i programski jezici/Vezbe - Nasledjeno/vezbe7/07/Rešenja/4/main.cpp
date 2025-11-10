#include "evidencijaLekova.hpp"

int main()
{
    cout << "Testiranje klase Lek" << endl << endl;

    DinString d("Pressing");
    Lek lek1, lek2(2, "Aspirin", 22.33, 10), lek3(3, d, 34.56, 20), lek4(lek3);

    cout << lek1 << endl;
    cout << lek2 << endl;
    cout << lek3 << endl;
    cout << lek4 << endl;


    cout << endl << endl;
    cout << "Testiranje klase EvidencijaLekova" << endl;

    EvidencijaLekova e;
    cout << e;

    cout << endl << endl;
    cout << "Dodavanje leka preko parametara" << endl;

    // ucitavanje parametara
    long jkl;
    char naziv[100];
    int jedinicnaCena, kolicina;

    cout << "Unesite jedinstveni kljuc leka (sifru leka): ";
    cin >> jkl;

    cout << "Unesite naziv leka: ";
    cin >> naziv;

    cout << "Unesite jedinicnu cenu leka: ";
    cin >> jedinicnaCena;

    cout << "Unesite kolicinu leka: ";
    cin >> kolicina;


    cout << endl;
    if(e.dodajLek(jkl, naziv, jedinicnaCena, kolicina)){
        cout << "Lek uspesno dodat." << endl;
        cout << e;
    } else {
        cout << "Greska prilikom dodavanja leka." << endl;
    }




    cout << endl << endl;
    cout << "Dodavanje vec napravljenog leka " << endl;

    if(e.dodajLek(lek2)){
        cout << "Lek ("<< lek2 << ") uspesno dodat." << endl;
        cout << e;
    } else {
        cout << "Greska prilikom dodavanja leka ("<< lek2 << ")." << endl;
    }

    if(e.dodajLek(lek3)){
        cout << "Lek ("<< lek3 << ") uspesno dodat." << endl;
        cout << e;
    } else {
        cout << "Greska prilikom dodavanja leka ("<< lek3 << ")." << endl;
    }


    cout << endl << endl;
    cout << "Sortiranje lekova po ukupnoj vrednosti" << endl;

    e.sortirajLekove();
    cout << e;


    cout << endl << endl;
    cout << "Uklanjanje leka" << endl;

    if(e.ukloniLek(1)){
        cout << "Lek na poziciji 1 uspesno uklonjen." << endl;
        cout << e;
    } else {
        cout << "Greska prilikom uklanjanja leka na poziciji 1." << endl;
    }

    if(e.ukloniLek(17)){
        cout << "Lek na poziciji 17 uspesno uklonjen." << endl;
        cout << e;
    } else {
        cout << "Greska prilikom uklanjanja leka na poziciji 17." << endl;
    }

    return 0;
}
