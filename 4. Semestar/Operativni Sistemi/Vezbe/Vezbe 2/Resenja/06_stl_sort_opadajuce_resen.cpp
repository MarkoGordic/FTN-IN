/*
Uneti 5 celih brojeva sa standardnog ulaza.
Koriscenjem STL algoritma sortirati brojeve u opadajucem redosledu
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//funkcija dobija 2 broja i vraca informaciju o tome da li je prvi broj veci od drugog
bool poredi(int a, int b) { return a > b; }

int main() {
    vector<int> brojevi; //STL vektor koji sadrzi brojeve koji treba da se sortiraju
    int broj; //privremena promenljiva u koju se ubacuje broj unesen sa tastature
    cout << "Unesite 5 celih brojeva:" << endl;
    for (int i = 0; i < 5; i++) { 
        cin >> broj; //zahtev za unos sa tastature - unesena vrednost se upisuje u promenljivu broj
        brojevi.push_back(broj); //uneseni broj se ubacuje na kraj STL kontejnera 
    }	
    //nakon unosa elemenata, vrsi se sortiranje
    
    //funkcija sort je definisana u zaglavlju algorithm
    //prvi parametar je iterator na element od kojeg se pocinje sortiranje
    //drugi parametar je iterator na element pre kojeg treba zavrsiti sortiranje
    //treci parametar je funkcija koja ce medjusobno porediti elemente i odluciti da li se elementima zamenjuju mesta u kontejneru
    //funkcija poredi ce se automatski pozvati potreban broj puta (kada god algoritam sortiranja treba da uporedi elemente kontejnera)		
    //rezultat funkcije "poredi" (true ili false) odredice da li algoritam treba da zameni mesta elementima koje je funkcija poredila		
    sort(brojevi.begin(), brojevi.end(), poredi);
    //ispis elemenata kontejnera nakon sortiranja	
    cout << "Sortirani brojevi: " << endl;
    vector<int>::const_iterator it;
    //prolazak kroz vektor od pocetka do kraja	
    for (it = brojevi.begin(); it != brojevi.end(); ++it) {
        cout << *it << endl; //ispis elementa na kojeg iterator pokazuje u trenutnoj iteraciji
    }
}
