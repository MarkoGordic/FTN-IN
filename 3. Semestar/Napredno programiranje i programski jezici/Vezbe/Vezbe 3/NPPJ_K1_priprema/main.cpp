#include <iostream>
using namespace std;

#include "Igra.hpp"

void ispisiIgru(const Igra& i){
    cout << "Trenutno stanje: ";
    switch(i.trenutnoStanje){
        case PROFIL_IGRACA:
            cout << "PROFIL_IGRACA" << endl;
            break;
        case IGRA_RACUNAR:
            cout << "IGRA_RACUNAR" << endl;
            break;
        case IGRA_PROTIVNIK:
            cout << "IGRA_PROTIVNIK" << endl;
            break;
    }

    i.igrac.ispis();
}

int meni(){
    int opcija;
    cout << "1. Prijavi igraca" << endl;
    cout << "2. Odjava igraca" << endl;
    cout << "3. Pocni igru sa racunarom" << endl;
    cout << "4. Pocni igru online" << endl;
    cout << "5. Pobedi" << endl;
    cout << "6. Izgubi" << endl;
    cout << "7. Ostvari bonus" << endl;
    cout << "8. Ispisi igru" << endl;
    cout << "9. Exit" << endl;
    cout << "Opcija: ";
    cin >> opcija;
    return opcija;
}

int main(){
    Igra i;
    int opcija;

    do{
        ispisiIgru(i);
        opcija = meni();

        switch(opcija){
            case 1:
                if(i.prijaviIgraca()){
                    cout << "Igrac je prijavljen" << endl;
                }else{
                    cout << "Ne mozete prijaviti igraca" << endl;
                }
                break;
            case 2:
                if(i.odjaviIgraca()){
                    cout << "Igrac je odjavljen" << endl;
                }else{
                    cout << "Ne mozete odjaviti igraca" << endl;
                }
                break;
            case 3:
                if(i.pocniIgruRacunar()){
                    cout << "Igra sa racunarom je pocela" << endl;
                }else{
                    cout << "Ne mozete poceti igru sa racunarom" << endl;
                }
                break;
            case 4:
                if(i.pocniIgruOnline()){
                    cout << "Igra online je pocela" << endl;
                }else{
                    cout << "Ne mozete poceti igru online" << endl;
                }
                break;
            case 5:
                if(i.pobedi()){
                    cout << "Pobedili ste" << endl;
                }else{
                    cout << "Niste pobedili" << endl;
                }
                break;
            case 6:
                if(i.izgubi()){
                    cout << "Izgubili ste" << endl;
                }else{
                    cout << "Niste izgubili" << endl;
                }
                break;
            case 7:
                if(i.ostvariBonus()){
                    cout << "Bonus je ostvaren" << endl;
                }else{
                    cout << "Ne mozete ostvariti bonus" << endl;
                }
                break;
            case 8:
                ispisiIgru(i);
                break;
            default:
                cout << "Nepostojeca opcija" << endl;
                break;
        }
    }while(opcija != 9);

    return 0;
}