#include <iostream>
using namespace std;

#include "automobil.hpp"

int meni(){
    int opcija;
    cout << "1. Upali automobil" << endl;
    cout << "2. Ugasi automobil" << endl;
    cout << "3. Pokvari automobil" << endl;
    cout << "4. Povecaj brzinu" << endl;
    cout << "5. Smanji brzinu" << endl;
    cout << "6. Izlaz" << endl;
    cout << "Unesite opciju: ";
    cin >> opcija;
    return opcija;
}

int main(){
    Automobil a;
    int opcija;

    do{
        a.toString();
        opcija = meni();

        switch(opcija){
            case 1:
                if(a.upali()){
                    cout << "Automobil je upaljen" << endl;
                }else{
                    cout << "Ne mozete upaliti automobil" << endl;
                }
                break;
            case 2:
                if(a.ugasi()){
                    cout << "Automobil je ugasen" << endl;
                }else{
                    cout << "Ne mozete ugasiti automobil" << endl;
                }
                break;
            case 3:
                if(a.pokvari()){
                    cout << "Automobil je pokvaren" << endl;
                }else{
                    cout << "Automobil je vec pokvaren" << endl;
                }
                break;
            case 4:
                if(a.povecajBrzinu()){
                    cout << "Brzina je povecana" << endl;
                }else{
                    cout << "Brzina je vec maksimalna" << endl;
                }
                break;
            case 5:
                if(a.smanjiBrzinu()){
                    cout << "Brzina je smanjena" << endl;
                }else{
                    cout << "Brzina je vec minimalna" << endl;
                }
                break;
            case 6:
                cout << "Izlaz" << endl;
                break;
            default:
                cout << "Nepostojeca opcija" << endl;
                break;
        }

    }while(opcija != 6);

    return 0;
}