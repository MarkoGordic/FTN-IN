// Modelovati prvo kolo teniskog turnira koje se odrzava u teniskom klubu sa n terena.
// Svaki teren ima svoj broj (Brojevi su od 1 do 12).
//
// Na terenima se igraju teniski mecevi prvog kola teniskog turnira. U prvom kolu ucestvuje X takmicara,
// tako da ima M = X/2 teniska meca. Za svaki mec u startu se definise na kojem terenu ce biti odigran.
// Raspored meceva po terenima pravi se tako da se mecevi ravnomerno rasporede po terenima. Znaci, na svakom terenu
// se u proseku igraju n/M meca. Svaki mec ima svoj identifikator (broj).
//
// Svaki mec traje slucajan vremenski period izmedju 1 i 5 sekundi. Naredni mec na terenu ne moze da pocne dok
// se prethodni mec na tom terenu ne zavrsi.
//
// Za svaki mec potrebno je evidentirati trenutak kada je mec poceo i koliko je mec trajao.
//
// Implementirati oznacene metode klase Teniski_klub u fajlu teniski_klub.h

#include <thread>

#include "teniski_klub.hpp"

using namespace std;

void mec(Teniski_klub& tk, int broj_meca, int na_terenu) {     //Nit meca. Prosledjuje se broj meca i na kom terenu se igra.
    tk.odigraj_mec(broj_meca, na_terenu);
}

void testirajSve() {
    int ukupno_terena = 3;
    Mec m;
    Teniski_klub tk(m, ukupno_terena);

    int broj_takmicara = 20;
    int broj_meceva = broj_takmicara/2;                           //Logicno, meceva ima polovina od broja takmicara.

    thread mecevi[broj_meceva];

    for (int i = 0; i < broj_meceva; ++i) {                  //Svi mecevi se ciklicno rasporedjuju na terene 1,2 i 3.
        mecevi[i] = thread(mec, ref(tk), i, i % ukupno_terena);
    }

    for (int i = 0; i < broj_meceva; ++i) {
        mecevi[i].join();
    }
}

int main() {
    testirajSve();

    return 0;
}
