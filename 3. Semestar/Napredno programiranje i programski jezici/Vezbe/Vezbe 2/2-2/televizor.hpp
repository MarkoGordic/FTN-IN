#ifndef TELEVIZOR_HPP_INCLUDED
#define TELEVIZOR_HPP_INCLUDED

enum StanjeTelevizora {
    UKLJUCEN,
    ISKLJUCEN,
    POKVAREN
};

class Televizor{
private:
    StanjeTelevizora stanje;
    int zvuk;
    int kanal;

public:
    Televizor();
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