#include "televizor.hpp"

Televizor::Televizor() {
    stanje = ISKLJUCEN;
    zvuk = 0;
    kanal = 1;
}

bool Televizor::ukljuci() {
    if (stanje == ISKLJUCEN) {
        stanje = UKLJUCEN;
        return true;
    }
    return false;
}

bool Televizor::iskljuci() {
    if (stanje == UKLJUCEN) {
        stanje = ISKLJUCEN;
        zvuk = 0;
        kanal = 1;
        return true;
    }
    return false;
}

bool Televizor::pokvari() {
    if (stanje != POKVAREN) {
        stanje = POKVAREN;
        zvuk = 0;
        kanal = 1;
        return true;
    }
    return false;
}

bool Televizor::popravi() {
    if (stanje == POKVAREN) {
        stanje = ISKLJUCEN;
        zvuk = 0;
        kanal = 1;
        return true;
    }
    return false;
}

bool Televizor::pojacajZvuk() {
    if (stanje == UKLJUCEN && zvuk + 1 <= 20) {
        zvuk++;
        return true;
    }
    return false;
}

bool Televizor::smanjiZvuk() {
    if (stanje == UKLJUCEN && zvuk - 1 >= 0) {
        zvuk--;
        return true;
    }
    return false;
}

bool Televizor::sledeciKanal() {
    if (stanje == UKLJUCEN && kanal + 1 <= 5) {
        kanal++;
        return true;
    }
    return false;
}

bool Televizor::prethodniKanal() {
    if (stanje == UKLJUCEN && kanal - 1 >= 1) {
        kanal--;
        return true;
    }
    return false;
}

StanjeTelevizora Televizor::getStanje() const {
    return stanje;
}

int Televizor::getZvuk() const {
    return zvuk;
}

int Televizor::getKanal() const {
    return kanal;
}