#include "rerna.hpp"

Rerna::Rerna() {
    temperatura = 0;
    trenutnoStanje = ISKLJUCENA;
}

bool Rerna::ukljuci() {
    if (trenutnoStanje == ISKLJUCENA) {
        trenutnoStanje = UKLJUCENA;
        temperatura += 20;
        return true;
    }
    return false;
}

bool Rerna::iskljuci() {
    if (trenutnoStanje == UKLJUCENA) {
        trenutnoStanje = ISKLJUCENA;
        temperatura = 0;
        return true;
    }
    return false;
}

bool Rerna::pokvari() {
    if (trenutnoStanje != POKVARENA) {
        trenutnoStanje = POKVARENA;
        temperatura = 0;
        return true;
    }
    return false;
}

bool Rerna::popravi() {
    if (trenutnoStanje == POKVARENA) {
        trenutnoStanje = ISKLJUCENA;
        temperatura = 0;
        return true;
    }
    return false;
}

bool Rerna::pojacajTemperaturu() {
    if (trenutnoStanje == UKLJUCENA && temperatura + 20 <= 220) {
        temperatura += 20;
        return true;
    }
    return false;
}

bool Rerna::smanjiTemperaturu() {
    if (trenutnoStanje == UKLJUCENA && temperatura - 20 >= 0) {
        temperatura -= 20;
        return true;
    }
    return false;
}

int Rerna::getTemperatura() const {
    return temperatura;
}

StanjeRerne Rerna::getTrenutnoStanje() const {
    return trenutnoStanje;
}