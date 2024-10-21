#include <iostream>
using namespace std;

bool prestupnaGodina(int godina){
    if(godina % 4 == 0 && godina % 100 != 0 || godina % 400 == 0)
        return true;
    return false;
}

int main(){
    int godina;
    cout << "Unesite godinu: ";
    cin >> godina;

    if(prestupnaGodina(godina))
        cout << "Godina je prestupna." << endl;
    else
        cout << "Godina nije prestupna." << endl;

    return 0;
}