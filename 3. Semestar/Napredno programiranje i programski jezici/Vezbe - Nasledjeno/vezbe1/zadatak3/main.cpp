#include <iostream>

using namespace std;

bool prestupna(int godina){
    /*if (godina % 4 == 0){
        if (godina % 100 == 0){
            if (godina % 400 == 0){
                cout << "Prestupna" << endl;
            }
            else {
                cout << "Nije prestupna" << endl;
            }
        }
        else if (godina % 100 != 0){
            cout << "Prestupna" << endl;
        }
    }
    else {
        cout << "Nije prestupna" << endl;
    }*/
    return (godina % 400 == 0 || (godina % 4 == 0 && godina % 100 != 0)) ? true : false;
}

int main()
{
    int godina = 0;
    cout << "Unesite godinu: ";
    cin >> godina;
    if (godina < 0){
        cout << "Greska" << endl;
        return 1;
    }

    if (prestupna(godina)){
        cout << "Prestupna" << endl;
    }
    else {
        cout << "Nije prestupna" << endl;
    }
    return 0;
}
