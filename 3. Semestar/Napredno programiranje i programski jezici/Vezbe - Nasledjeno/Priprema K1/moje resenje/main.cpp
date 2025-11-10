#include <iostream>
#include <cstdlib>

using namespace std;

#include "igrac.hpp"
#include "igra.hpp"

void ispisiIgru(const Igra& igra){
    cout << "IGRA" << endl;
    cout << "Trenutno Stanje: ";
    switch (igra.trenutnoStanje){
        case NEPOZNAT_IGRAC:
            cout << "NEPOZNAT IGRAC" ;
            break;
        case PROFIL_IGRACA:
            cout << "PROFIL IGRACA" ;
            break;
        case IGRA_RACUNAR:
            cout << "IGRA RACUNAR" ;
            break;
        case IGRA_PROTIVNIK:
            cout << "IGRA PROTIVNIK" ;
            break;
        default:
            cout << "NEPOZNATO STANJE";
    }
    cout << endl;
    igra.igrac.ispis();
}

int meni() {
    int n = 0;
    cout << "OPCIJA 1: PRIJAVA IGRACA" << endl;
    cout << "OPCIJA 2: ODJAVA IGRACA" << endl;
    cout << "OPCIJA 3: POCNI IGRU RACUNAR" << endl;
    cout << "OPCIJA 4: POCNI IGRU ONLINE" << endl;
    cout << "OPCIJA 5: POBEDI IGRU" << endl;
    cout << "OPCIJA 6: IZGUBI IGRU" << endl;
    cout << "OPCIJA 7: OTVORI BONUS" << endl;
    cout << "OPCIJA 0: IZLAZ" << endl;
    cout << "OPCIJA: ";
    cin >> n;
    return n;
}

void ispisUspesnosti(bool success) {
    cout << ( (success) ? "USPESNO" : "NEUSPESNO") << endl;
}

int main()
{
    srand(time(0));

    /// TESTIRANJE IGRACA
    Igrac ii1, ii2(3, 2);
    ii1.ispis();
    ii1.dodajPoene(4);
    ii1.odigrajPartiju();
    ii1.getBrojPartija();
    ii1.getPoeni();
    ii1.ispis();

    ii2.ispis();
    ii2.resetuj();
    ii2.setPoeni(5);
    ii2.ispis();

    /// TESTIRANJE IGRE CEMO KROZ MENI
    Igra i1, i2(3, 3, PROFIL_IGRACA);

    int opcija;
    do {
        opcija = meni();
        switch(opcija){
            case 1: ispisUspesnosti(i2.prijaviIgraca()); break;
            case 2: ispisUspesnosti(i2.odjaviIgraca()); break;
            case 3: ispisUspesnosti(i2.pocniIgruRacunar()); break;
            case 4: ispisUspesnosti(i2.pocniIgruOnline()); break;
            case 5: ispisUspesnosti(i2.pobedi()); break;
            case 6: ispisUspesnosti(i2.izgubi()); break;
            case 7: ispisUspesnosti(i2.otvoriBonus()); break;
            case 0: cout << "POZDRAVKO!" << endl; break;
            default: cout << "NEPOSTOJECA OPCIJA!" << endl;
        }
        ispisiIgru(i2);
    } while(opcija != 0);

    return 0;
}
