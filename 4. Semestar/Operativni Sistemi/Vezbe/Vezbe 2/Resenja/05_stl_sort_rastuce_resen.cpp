/*
Uneti 5 celih brojeva sa standardnog ulaza.
Koriscenjem STL algoritma sortirati brojeve u rastucem redosledu
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<int> brojevi; //STL vektor koji sadrzi brojeve koji treba da se sortiraju
    int broj; //privremena promenljiva u koju se ubacuje broj unesen sa tastature
    cout << "Unesite 5 celih brojeva:" << endl;
    for (int i = 0; i < 5; i++) {
        cin >> broj; //zahtev za unos sa tastature - unesena vrednost se upisuje u promenljivu broj
        brojevi.push_back(broj); //uneseni broj se ubacuje na kraj STL kontejnera 
    }
    //nakon unosa elemenata, vrsi se sortiranje
    //prvi parametar je iterator na element od kojeg se pocinje sortiranje
    //drugi parametar je iterator na element pre kojeg treba zavrsiti sortiranje	
    //posto nije navedena funkcija koja opisuje poredjenje elemenata, primenjuje se default poredjenje
    //zato ce se sortiranje izvrsiti u rastucem redosledu		
    sort(brojevi.begin(), brojevi.end());
    //ispis elemenata kontejnera nakon sortiranja
    cout << "Sortirani brojevi: " << endl;
    vector<int>::const_iterator it;
    //prolazak kroz vektor od pocetka do kraja	
    for (it = brojevi.begin(); it != brojevi.end(); ++it) {
        cout << *it << endl; //ispis elementa na kojeg iterator pokazuje u trenutnoj iteraciji
    }
}
