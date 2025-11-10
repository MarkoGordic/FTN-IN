#ifndef RERNA_H_INCLUDED
#define RERNA_H_INCLUDED

#include <iostream>
using namespace std;

#define TEMPERATURA_MINIMUM 0
#define TEMPERATURA_MAKSIMUM 220
#define TEMPERATURA_KORAK 20

enum StanjeRerne {ISKLJUCENA, UKLJUCENA, POKVARENA};

class Rerna{
    private:
        StanjeRerne trenutnoStanje;
        int temperatura;

    public:
        Rerna() {
            trenutnoStanje = ISKLJUCENA;
            temperatura = TEMPERATURA_MINIMUM;
        }

        bool ukljuci() {
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

        bool iskljuci() {
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

        bool pokvari() {
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

        bool popravi() {
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

        bool pojacajTemperaturu() {
            bool uspesno;

            if (trenutnoStanje == UKLJUCENA && temperatura + TEMPERATURA_KORAK <= TEMPERATURA_MAKSIMUM) {
                temperatura += TEMPERATURA_KORAK;
                uspesno = true;
            } else {
                uspesno = false;
            }

            return uspesno;
        }

        bool smanjiTemperaturu() {
            bool uspesno;

            if (trenutnoStanje == UKLJUCENA && temperatura - TEMPERATURA_KORAK >= TEMPERATURA_MINIMUM) {
                temperatura -= TEMPERATURA_KORAK;
                uspesno = true;
            } else {
                uspesno = false;
            }

            return uspesno;
        }

        StanjeRerne getTrenutnoStanje() const { return trenutnoStanje; }
        int getTemperatura() const { return temperatura; }
};

#endif // RERNA_H_INCLUDED

