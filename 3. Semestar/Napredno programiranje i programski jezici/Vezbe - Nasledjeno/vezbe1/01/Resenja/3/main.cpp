#include <iostream>
using namespace std;

//Godina je prestupna ako je deljiva sa 4 - osim onih koje su deljive sa 100 i nisu deljive sa 400 u isto vreme.
bool jePrestupna(int godina){

    bool prestupna;

    if (godina % 4 != 0) {
        prestupna = false;
    } else if (godina % 400 == 0) {
        prestupna = true;
    } else if (godina % 100 == 0){
        prestupna = false;
    } else {
        prestupna = true;
    }

    return prestupna;
}

int main()
{
    int godina;

    cout << "Unesite godinu:" << endl;
    cin >> godina;

    bool rezultat = jePrestupna(godina);

    // cout << rezultat << endl; // ovako dobijemo 0 ili 1

    if (rezultat == true){
        cout << "Godina " << godina << ". je prestupna";
    } else {
        cout << "Godina " << godina << ". nije prestupna";
    }

    return 0;
}
