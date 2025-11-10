#include "televizor.hpp"

Televizor::Televizor(){
    stanje = ISKLJUCEN;
    zvuk = MIN_ZVUK;
    kanal = MIN_KANAL;
}

Televizor::Televizor(const Televizor& t){
    stanje = t.stanje;
    zvuk = t.zvuk;
    kanal = t.kanal;
}

bool Televizor::ukljuci(){
    bool success;
    if (stanje == ISKLJUCEN){
        stanje = UKLJUCEN;
        success = true;
    }
    else {
        success = false;
    }
    return success;
}

bool Televizor::iskljuci(){
    bool success;
    if (stanje == UKLJUCEN){
        stanje = ISKLJUCEN;
        zvuk = MIN_ZVUK;
        kanal = MIN_KANAL;
        success = true;
    }
    else {
        success = false;
    }
    return success;
}

bool Televizor::pokvari(){
    bool success;
    if (stanje != POKVAREN){
        stanje = POKVAREN;
        zvuk = POKVAREN_ZVUK;
        kanal = POKVAREN_KANAL;
        success = true;
    }
    else {
        success = false;
    }
    return success;
}

bool Televizor::popravi(){
    bool success;
    if (stanje == POKVAREN){
        stanje = ISKLJUCEN;
        success = true;
    }
    else {
        success = false;
    }
    return success;
}

bool Televizor::pojacajZvuk(){
    bool success;
    if (stanje == UKLJUCEN && zvuk + KORAK_ZVUK <= MAX_ZVUK){
        zvuk += KORAK_ZVUK;
        success = true;
    }
    else {
        success = false;
    }
    return success;
}

bool Televizor::smanjiZvuk(){
    bool success;
    if (stanje == UKLJUCEN && zvuk - KORAK_ZVUK >= MIN_ZVUK){
        zvuk -= KORAK_ZVUK;
        success = true;
    }
    else {
        success = false;
    }
    return success;
}

bool Televizor::sledeciKanal(){
    bool success;
    if (stanje == UKLJUCEN && kanal + KORAK_KANAL <= MAX_KANAL){
        kanal += KORAK_KANAL;
        success = true;
    }
    else {
        success = false;
    }
    return success;
}

bool Televizor::prethodniKanal(){
    bool success;
    if (stanje == UKLJUCEN && kanal - KORAK_KANAL >= MIN_KANAL){
        kanal -= KORAK_KANAL;
        success = true;
    }
    else {
        success = false;
    }
    return success;
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
