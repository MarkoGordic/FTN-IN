#ifndef TELEFONGEN2_HPP_INCLUDED
#define TELEFONGEN2_HPP_INCLUDED

#include "Telefon.hpp"
#include "Kamera.hpp"

class TelefonGen2 : public Telefon {
protected:
    Kamera k;
public:
    TelefonGen2() : Telefon(), k() {}
    TelefonGen2(DinString broj, int megaPikseli, int freeSpace) : Telefon(broj), k(megaPikseli, freeSpace) {}

    bool dodajSliku() {
        return k.slikaj();
    }
};

#endif // TELEFONGEN2_HPP_INCLUDED