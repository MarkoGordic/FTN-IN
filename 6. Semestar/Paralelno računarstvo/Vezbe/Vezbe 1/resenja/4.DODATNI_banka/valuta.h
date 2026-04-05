#ifndef VALUTA_H_INCLUDED
#define VALUTA_H_INCLUDED

#include <string>

using namespace std;

enum Valuta {DINAR = 0, EURO}; // Tipovi valuta

string naziv_valute(Valuta valuta) {
    if (valuta == Valuta::DINAR)
        return "DIN";
    else
        return "EUR";
}

#endif // VALUTA_H_INCLUDED
