#include "televizor.hpp"

int meni(){
    int n;

    cout << "Izaberite operaciju" << endl;
    cout << " 1. ukljuci" << endl;
    cout << " 2. iskljuci" << endl;
    cout << " 3. pokvari" << endl;
    cout << " 4. popravi" << endl;
    cout << " 5. pojacaj zvuk" << endl;
    cout << " 6. smanji zvuk" << endl;
    cout << " 7. sledeci kanal" << endl;
    cout << " 8. prethodni kanal" << endl;
    cout << " 9. prikazi stanje" << endl;
    cout << "10. kraj rada programa" << endl;
    cout << "Operacija-> ";

    cin >> n;
    return n;
}

// ova funkcija nije trazena u zadatku i nije neophodna,
// ali smanjuje kolicinu koda i olaksava citljivost istog
void ispisUspeha(bool upit){
    if (upit)
        cout << "Operacija je izvrsena" << endl;
    else
        cout << "Operacija nije izvrsena" << endl;
}

void ispis(const Televizor &tv) {
    cout << "TV: ";

    cout << "STANJE - ";
    switch (tv.getStanje()) {
        case UKLJUCEN:
            cout << "ukljucen";
            break;
        case ISKLJUCEN:
            cout << "iskljucen";
            break;
        case POKVAREN:
            cout << "pokvaren";
            break;
        default:
            cout << "nedefinisano";
    }

    cout << ", ZVUK: " << tv.getZvuk() << ", KANAL: " << tv.getKanal() << endl;
}


int main()
{
    cout << "Testiranje prvog konstruktora" << endl;
    Televizor tv1;
    ispis(tv1);
    cout << endl;

    cout << "Testiranje metoda i funkcija" << endl;
    int n;
    do{
        cout << endl;
        n = meni();
        cout << endl;

        switch (n) {
            case 1:
                ispisUspeha(tv1.ukljuci());
                break;
            case 2:
                ispisUspeha(tv1.iskljuci());
                break;
            case 3:
                ispisUspeha(tv1.pokvari());
                break;
            case 4:
                ispisUspeha(tv1.popravi());
                break;
            case 5:
                ispisUspeha(tv1.pojacajZvuk());
                break;
            case 6:
                ispisUspeha(tv1.smanjiZvuk());
                break;
            case 7:
                ispisUspeha(tv1.sledeciKanal());
                break;
            case 8:
                ispisUspeha(tv1.prethodniKanal());
                break;
            case 9:
                // umesto ove opcije u meniju moze se ispisati stanje posle svake operacije
                ispis(tv1);
                break;
            case 10:
                cout << "Kraj rada programa" << endl;
                break;
            default:
                cout << "Nepostojeca operacija" << endl;
                break;
        }
    } while(n != 10);
    cout << endl;

    cout << "Testiranje drugog konstruktora" << endl;
    Televizor tv2(tv1);
    ispis(tv2);

    return 0;
}
