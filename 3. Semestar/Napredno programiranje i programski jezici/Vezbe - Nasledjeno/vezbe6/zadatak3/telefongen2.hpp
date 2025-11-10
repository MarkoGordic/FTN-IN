#ifndef TELEFONGEN2_HPP_INCLUDED
#define TELEFONGEN2_HPP_INCLUDED

class TelefonGen2 : public Telefon {
private:
    Kamera k;
public:
    TelefonGen2 () : Telefon (), k () {}

    TelefonGen2 (const DinString& br, int mp, int fs) : Telefon (br), k(mp, fs) {}

    int getPhotoCounter () const {
        return k.getPhotoCounter();
    }

    bool slikajSliku () {
        return k.slikaj();
    }
};

#endif // TELEFONGEN2_HPP_INCLUDED
