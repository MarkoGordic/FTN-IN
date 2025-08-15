#ifndef KREDIT_HPP_INCLUDED
#define KREDIT_HPP_INCLUDED

#include <iostream>
#include <mutex>

#include "valuta.hpp"

using namespace std;

class Kredit {
private:
    mutex terminal;
public:
    // rbr - Redni broj klijenta
    // svota - Novčani iznos koji je potreban klijentu
    // valuta - Valuta u kojem je novčani iznos
    void ceka(int rbr, int svota, Valuta valuta) {
        unique_lock<mutex> u(terminal);
       cout << "Klijent: " << rbr << " mora da ceka kako bi dobio kredit od " << svota << " " << naziv_valute(valuta) << endl;
    }

    // rbr - Redni broj klijenta
    // svota - Novčani iznos koji je potreban klijentu
    // saldo - Ukupna raspoloživa sredstva u banci za traženu valutu (nakon odobrenja kredita)
    // valuta - Valuta u kojem je novčani iznos
    void dobio(int rbr, int svota, int saldo, Valuta valuta) {
        unique_lock<mutex> u(terminal);
        cout << "Klijent: " << rbr << " dobio " << svota << ", u banci ostalo: " << saldo << ", valuta: " << naziv_valute(valuta) << endl;
    }

    // rbr - Redni broj klijenta
    // svota - Novčani iznos koji je potreban klijentu
    // saldo - Ukupna raspoloživa sredstva u banci za traženu valutu (nakon što je iznos kredita vraćen)
    // valuta - Valuta u kojem je novčani iznos
    void vratio(int rbr, int svota, int saldo, Valuta valuta) {
        unique_lock<mutex> u(terminal);
        cout << "Klijent: " << rbr << " vratio " << svota << ", u banci ostalo: " << saldo << ", valuta: " << naziv_valute(valuta) << endl;
}
};

#endif // KREDIT_HPP_INCLUDED
