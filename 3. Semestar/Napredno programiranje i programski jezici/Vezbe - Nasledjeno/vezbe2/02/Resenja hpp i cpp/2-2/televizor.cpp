#include "Televizor.hpp"

Televizor::Televizor() {
    stanje = ISKLJUCEN;
    zvuk = ZVUK_MINIMUM;
    kanal = KANAL_MINIMUM;
}

Televizor::Televizor(const Televizor &t) {
    stanje = t.stanje;
    zvuk = t.zvuk;
    kanal = t.kanal;
}

int Televizor::getZvuk() const {
    return zvuk;
}

int Televizor::getKanal() const {
    return kanal;
}

StanjeTelevizora Televizor::getStanje() const {
    return stanje;
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
        zvuk = ZVUK_MINIMUM;
        kanal = KANAL_MINIMUM;
        return true;
    }
    return false;
}

bool Televizor::pokvari() {
    if (stanje != POKVAREN) {
        stanje = POKVAREN;
        zvuk = ZVUK_POKVAREN;
        kanal = KANAL_POKVAREN;
        return true;
    }
    return false;
}

bool Televizor::popravi() {
    if (stanje == POKVAREN) {
        stanje = ISKLJUCEN;
        zvuk = ZVUK_MINIMUM;
        kanal = KANAL_MINIMUM;
        return true;
    }
    return false;
}

bool Televizor::pojacajZvuk() {
    if (stanje == UKLJUCEN && zvuk + ZVUK_KORAK <= ZVUK_MAKSIMUM) {
        zvuk += ZVUK_KORAK;
        return true;
    }
    return false;
}

bool Televizor::smanjiZvuk() {
    if (stanje == UKLJUCEN && zvuk - ZVUK_KORAK >= ZVUK_MINIMUM) {
        zvuk -= ZVUK_KORAK;
        return true;
    }
    return false;
}

bool Televizor::sledeciKanal() {
    if (stanje == UKLJUCEN && kanal + KANAL_KORAK <= KANAL_MAKSIMUM) {
        kanal += KANAL_KORAK;
        return true;
    }
    return false;
}

bool Televizor::prethodniKanal() {
    if (stanje == UKLJUCEN && kanal - KANAL_KORAK >= KANAL_MINIMUM) {
        kanal -= KANAL_KORAK;
        return true;
    }
    return false;
}
