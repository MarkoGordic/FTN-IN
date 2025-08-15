/*
Uneti 5 celih brojeva sa standardnog ulaza.
Koriscenjem STL algoritma pronaci najveci uneti broj
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<int> brojevi;  //STL vektor koji sadrzi brojeve koji treba da se sortiraju
    int broj;  //privremena promenljiva u koju se ubacuje broj unesen sa tastature
    cout << "Unesite 5 celih brojeva:" << endl;
    for (int i = 0; i < 5; i++) {
        cin >> broj;  //zahtev za unos sa tastature - unesena vrednost se upisuje u promenljivu broj
        brojevi.push_back(broj); //uneseni broj se ubacuje na kraj STL kontejnera 
    } 

    //pronalazenje najveceg elementa u kontejneru koriscenjem funkcije max_element iz zaglavlja algorithm
    //prvi parametar je iterator na element od kojeg se pocinje trazenje
    //drugi parametar je iterator na element pre kojeg treba zavrsiti trazenje (metoda end() vraca iterator iza poslednjeg elementa)
    //metoda vraca iterator na najveci element
    //dereferenciranjem ovog iteratora pristupa se najvecem elementu, sto se upisuje u promenljivu najveci
    int najveci = *max_element(brojevi.begin(), brojevi.end());
    cout << "Najveci broj je: " << najveci << endl;
}