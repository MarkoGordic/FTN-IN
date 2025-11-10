#ifndef TV_HPP_INCLUDED
#define TV_HPP_INCLUDED

#include <iostream>
using namespace std;

#define ZVUK_MINIMUM 0
#define ZVUK_MAKSIMUM 20
#define ZVUK_KORAK 1
#define ZVUK_POKVAREN 0

#define KANAL_MINIMUM 1
#define KANAL_MAKSIMUM 5
#define KANAL_KORAK 1
#define KANAL_POKVAREN 1

enum StanjeTelevizora {UKLJUCEN, ISKLJUCEN, POKVAREN};

class Televizor{
    private:
        StanjeTelevizora stanje;
        int zvuk;
        int kanal;
    public:
        Televizor() {
            stanje = ISKLJUCEN;
            zvuk = ZVUK_MINIMUM;
            kanal = KANAL_MINIMUM;
        }

        Televizor(const Televizor &t) {
            stanje = t.stanje;
            zvuk = t.zvuk;
            kanal = t.kanal;
        }

        int getZvuk() const { return zvuk; }
        int getKanal() const { return kanal; }
        StanjeTelevizora getStanje() const { return stanje; }

        bool ukljuci() {
            if (stanje == ISKLJUCEN) {
                stanje = UKLJUCEN;
                return true;
            }
            return false;
        }

        bool iskljuci() {
            if (stanje == UKLJUCEN) {
                stanje = ISKLJUCEN;
                zvuk = ZVUK_MINIMUM;
                kanal = KANAL_MINIMUM;
                return true;
            }
            return false;
        }

        bool pokvari() {
            if (stanje != POKVAREN) {
                stanje = POKVAREN;
                zvuk = ZVUK_POKVAREN;
                kanal = KANAL_POKVAREN;
                return true;
            }
            return false;
        }

        bool popravi() {
            if (stanje == POKVAREN) {
                stanje = ISKLJUCEN;
                zvuk = ZVUK_MINIMUM;
                kanal = KANAL_MINIMUM;
                return true;
            }
            return false;
        }

        bool pojacajZvuk() {
            if (stanje == UKLJUCEN && zvuk + ZVUK_KORAK <= ZVUK_MAKSIMUM) {
                zvuk += ZVUK_KORAK;
                return true;
            }
            return false;
        }

        bool smanjiZvuk() {
            if (stanje == UKLJUCEN && zvuk - ZVUK_KORAK >= ZVUK_MINIMUM) {
                zvuk -= ZVUK_KORAK;
                return true;
            }
            return false;
        }

        bool sledeciKanal() {
            if (stanje == UKLJUCEN && kanal + KANAL_KORAK <= KANAL_MAKSIMUM) {
                kanal += KANAL_KORAK;
                return true;
            }
            return false;
        }

        bool prethodniKanal() {
            if (stanje == UKLJUCEN && kanal - KANAL_KORAK >= KANAL_MINIMUM) {
                kanal -= KANAL_KORAK;
                return true;
            }
            return false;
        }
};

#endif // TV_HPP_INCLUDED
