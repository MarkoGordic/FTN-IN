#include "rerna.hpp"

Rerna::Rerna(){
    trenutnoStanje = ISKLJUCENA;
    temperatura = MIN_TEMPERATURA;
}

bool Rerna::ukljuci(){
    if (trenutnoStanje == ISKLJUCENA){
        temperatura += KORAK;
        trenutnoStanje = UKLJUCENA;
        return true;
    }
    return false;
}

bool Rerna::iskljuci(){
    if (trenutnoStanje == UKLJUCENA){
        temperatura = MIN_TEMPERATURA;
        trenutnoStanje = ISKLJUCENA;
        return true;
    }
    return false;
}

bool Rerna::pokvari(){
    if (trenutnoStanje != POKVARENA){
        temperatura = MIN_TEMPERATURA;
        trenutnoStanje = POKVARENA;
        return true;
    }
    return false;
}

bool Rerna::popravi(){
    if (trenutnoStanje == POKVARENA){
        temperatura = MIN_TEMPERATURA;      // moze i bez ovoga :)
        trenutnoStanje = ISKLJUCENA;
        return true;
    }
    return false;
}

bool Rerna::pojacajTemperaturu(){
    if (trenutnoStanje == UKLJUCENA && temperatura + KORAK <= MAX_TEMPERATURA){
        temperatura += KORAK;
        return true;
    }
    return false;
}

bool Rerna::smanjiTemperaturu(){
    if (trenutnoStanje == UKLJUCENA && temperatura - KORAK >= MIN_TEMPERATURA){
        temperatura -= KORAK;
        return true;
    }
    return false;
}

StanjeRerne Rerna::getTrenutnoStanje() const {
    return trenutnoStanje;
}

int Rerna::getTemperatura() const {
    return temperatura;
}
