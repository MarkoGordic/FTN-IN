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
        Televizor();
        Televizor(const Televizor &);

        int getZvuk() const;
        int getKanal() const;
        StanjeTelevizora getStanje() const;

        bool ukljuci();
        bool iskljuci();
        bool pokvari();
        bool popravi();

        bool pojacajZvuk();
        bool smanjiZvuk();

        bool sledeciKanal();
        bool prethodniKanal();
};

#endif // TV_HPP_INCLUDED
