#include "kocka.hpp"

//definisanje konstante
#define KRAJ_RADA 3

int meni(){
    cout << "Izaberite operaciju" << endl;
    cout << "1. Baci kocku" << endl;
    cout << "2. Prikazi kocku" << endl;
    cout << "3. Kraj" << endl;
    cout << "Operacija-> ";
    int n;
    cin >> n;
    return n;
}

int main()
{
    srand(time(0)); //da ne bi uvek generisao slucajne brojeve istim redosledom

    // konstruktor bez parametara
    Kocka k1;
    // konstruktor sa parametrima
    Kocka k2(3);
    // konstruktor kopije
    Kocka k3(k2);

    int n;
    do{
        n = meni();

        switch(n){
            case 1: // baci
                k1.baci();
                cout << endl << "Kocka je bacena" << endl << endl;
                break;
            case 2: // prikazi
                cout << endl << "Vrednost kocke je: " << k1.getVrednost() << endl << endl;
                break;
            case 3: // kraj rada programa
                cout << endl << "Kraj rada programa " << endl << endl;
                break;
            default:
                cout << endl << "Nepostojeca operacija" << endl << endl;
                break;
        }
    } while(n != KRAJ_RADA);

    return 0;
}
