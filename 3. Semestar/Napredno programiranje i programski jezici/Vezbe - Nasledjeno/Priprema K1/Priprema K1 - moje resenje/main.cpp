#include <iostream>

using namespace std;

#include "igrac.hpp"
#include "igra.hpp"

void ispisiIgru(const Igra& igra) {
    cout << "---- INFORMACIJE O IGRI ----" << endl;
    igra.igrac.ispis();
    cout << "Stanje igre: ";
    switch (igra.trenutnoStanje){
        case NEPOZNAT_IGRAC: cout << "NEPOZNAT IGRAC"; break;
        case PROFIL_IGRACA: cout << "PROFIL IGRACA"; break;
        case IGRA_RACUNAR: cout << "IGRA RACUNAR"; break;
        case IGRA_PROTIVNIK: cout << "IGRA PROTIVNIK"; break;
        default: cout << "NEPOSTOJECA OPCIJA!";
    }
    cout << endl;
    cout << "----------------------------" << endl;
}

int meni () {
    int n = 0;
    cout << "Opcija 1: Prijavi igraca" << endl;
    cout << "Opcija 2: Odjavi igraca" << endl;
    cout << "Opcija 3: Pocni igru racunar" << endl;
    cout << "Opcija 4: Pocni igru online" << endl;
    cout << "Opcija 5: Pobedi" << endl;
    cout << "Opcija 6: Izgubi" << endl;
    cout << "Opcija 7: Otvori bonus" << endl;
    cout << "Opcija 0: Izlaz" << endl;

    cout << "Opcija: ";
    cin >> n;
    return n;
}

void ispisUspeha (bool uspeh){
    cout << ((uspeh) ? "USPESNO" : "NEUSPESNO") << endl;
}

int main()
{
    Igrac i1, i2(3, 4);
    i2.ispis();
    i2.dodajPoene(4);
    i2.odigrajPartiju();
    i2.ispis();

    i2.resetuj();
    i2.ispis();

    i2.setPoeni(6);
    cout << "Broj poena: " << i2.getPoeni() << endl;

    i2.setBrojPartija(4);
    cout << "Broj partija: " << i2.getBrojPartija() << endl << endl;

    Igra ii1, ii2(3, 5, PROFIL_IGRACA);
    int opcija = 0;
    do {
        ispisiIgru(ii2);
        opcija = meni();

        switch (opcija) {
            case 1: ispisUspeha(ii2.prijaviIgraca()); break;
            case 2: ispisUspeha(ii2.odjaviIgraca()); break;
            case 3: ispisUspeha(ii2.pocniIgruRacunar()); break;
            case 4: ispisUspeha(ii2.pocniIgruOnline()); break;
            case 5: ispisUspeha(ii2.pobedi()); break;
            case 6: ispisUspeha(ii2.izgubi()); break;
            case 7: ispisUspeha(ii2.otvoriBonus()); break;
            case 0: cout << "Pozdrav!" << endl; break;
            default: cout << "Nepostojeca opcija!" << endl;
        }
    } while (opcija != 0);
    return 0;
}
