#ifndef TELEVIZOR_HPP_INCLUDED
#define TELEVIZOR_HPP_INCLUDED

#define MAX_ZVUK 20
#define MIN_ZVUK 0
#define KORAK_ZVUK 1
#define POKVAREN_ZVUK 0

#define MAX_KANAL 5
#define MIN_KANAL 1
#define KORAK_KANAL 1
#define POKVAREN_KANAL 1

enum StanjeTelevizora {UKLJUCEN, ISKLJUCEN, POKVAREN};

class Televizor {
private:
    StanjeTelevizora stanje;
    int zvuk;
    int kanal;
public:
    Televizor();
    Televizor(const Televizor&);
    bool ukljuci();
    bool iskljuci();
    bool pokvari();
    bool popravi();
    bool pojacajZvuk();
    bool smanjiZvuk();
    bool sledeciKanal();
    bool prethodniKanal();
    StanjeTelevizora getStanje() const;
    int getZvuk() const;
    int getKanal() const;
};

#endif // TELEVIZOR_HPP_INCLUDED
