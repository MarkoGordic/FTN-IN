#include "rerna.hpp"

// prazan konstruktor
Rerna::Rerna(){
    trenutnoStanje = ISKLJUCENA;
    temperatura = TEMPERATURA_MINIMUM;
}

// metoda koja ukljucuje rernu
// rerna se moze ukljuciti samo ako je iskljucena
bool Rerna::ukljuci(){
    bool uspesno;

    if (trenutnoStanje == ISKLJUCENA) {
        trenutnoStanje = UKLJUCENA;
        temperatura += TEMPERATURA_KORAK;
        uspesno = true;
    } else {
        uspesno = false;
    }

    return uspesno;
}

// metoda koja iskljucuje rernu
// rerna se moze iskljuciti samo ako je ukljucena
bool Rerna::iskljuci(){
    bool uspesno;

    if (trenutnoStanje == UKLJUCENA) {
        trenutnoStanje = ISKLJUCENA;
        temperatura = TEMPERATURA_MINIMUM;
        uspesno = true;
    } else {
        uspesno = false;
    }

    return uspesno;
}

// metoda koja kvari rernu
// rerna se moze pokvariti ako je ukljucena ili iskljucena
// != znaci ako nije
bool Rerna::pokvari(){
    bool uspesno;

    if (trenutnoStanje != POKVARENA) {
        trenutnoStanje = POKVARENA;
        temperatura = TEMPERATURA_MINIMUM;
        uspesno = true;
    } else {
        uspesno = false;
    }

    return uspesno;
}

// metoda koja popravlja rernu
// rerna se moze popraviti (prelazi u stanje iskljucena) samo ako je pokvarena
bool Rerna::popravi(){
    bool uspesno;

    if (trenutnoStanje == POKVARENA) {
        trenutnoStanje = ISKLJUCENA;
        temperatura = TEMPERATURA_MINIMUM;
        uspesno = true;
    } else {
        uspesno = false;
    }

    return uspesno;
}

// temperatura se moze pojacati samo ako je rerna ukljucena
bool Rerna::pojacajTemperaturu(){
    bool uspesno;

    // pre pojacavanja temperature treba proveriti da li ce biti probijena gornja granica
    if (trenutnoStanje == UKLJUCENA && temperatura + TEMPERATURA_KORAK <= TEMPERATURA_MAKSIMUM) {
        temperatura += TEMPERATURA_KORAK;
        uspesno = true;
    } else {
        uspesno = false;
    }

    return uspesno;
}

// temperatura se moze smanjiti samo ako je rerna ukljucena
bool Rerna::smanjiTemperaturu(){
    bool uspesno;

    // pre smanjivanja temperature treba proveriti da li ce biti probijena donja granica
    if (trenutnoStanje == UKLJUCENA && temperatura - TEMPERATURA_KORAK >= TEMPERATURA_MINIMUM) {
        temperatura -= TEMPERATURA_KORAK;
        uspesno = true;
    } else {
        uspesno = false;
    }

    return uspesno;
}

StanjeRerne Rerna::getTrenutnoStanje() const{
    return trenutnoStanje;
}

int Rerna::getTemperatura() const {
    return temperatura;
}



