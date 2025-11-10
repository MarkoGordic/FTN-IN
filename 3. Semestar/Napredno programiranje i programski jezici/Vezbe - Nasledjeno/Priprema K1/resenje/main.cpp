#include "igra.hpp"

void ispisiIgru(const Igra& igra){
    cout<<"--- IGRA ---"<<endl;
    cout<<"Igrac: "<<endl;
    igra.i.ispis(); //poziv metode za ispis iz igraca. posto ej prijateljska funkcija direktno mogu pristupiti polju i koje je private
    cout<<"Trenutno stanje igre: ";
    switch(igra.trenutnoStanje){ //posto je prijateljska funkcija direktno mogu pristupiti private polju
        case NEPOZNAT_IGRAC:
            cout<<"NEPOZNAT_IGRAC"<<endl;
            break;
        case IGRA_PROTIVNIK:
            cout<<"IGRA_PROTIVNIK"<<endl;
            break;
        case IGRA_RACUNAR:
            cout<<"IGRA_RACUNAR"<<endl;
            break;
        case PROFIL_IGRACA:
            cout<<"PROFIL_IGRACA"<<endl;
            break;
        default:
            cout<<"greska"<<endl;
    }
}

int main()
{
    Igrac i;
    Igrac i1(2, 3);
    Igrac i2(i);
    i.setPoeni(0);
    i.dodajPoene(1);
    i.ispis();
    i.getBrojPartija();
    i.getPoeni();
    i.odigrajPartiju();
    i.resetuj();

    Igra ig;
    Igra ig2(1, 2, IGRA_RACUNAR);
    ig.prijaviIgraca();
    ispisiIgru(ig);
    ig.odjaviIgraca();
    ig.pobedi();
    ig.izgubi();
    ig.pocniIgruOnline();
    ig.pocniIgruRacunar();
    ig.ostvariBonus();
    ispisiIgru(ig2);

    return 0;
}
