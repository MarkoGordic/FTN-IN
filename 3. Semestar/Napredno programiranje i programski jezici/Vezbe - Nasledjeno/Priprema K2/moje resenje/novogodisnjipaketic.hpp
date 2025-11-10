#ifndef NOVOGODISNJIPAKETIC_HPP_INCLUDED
#define NOVOGODISNJIPAKETIC_HPP_INCLUDED

class NovogodisnjiPaketic : public Paketic {
private:
    int minimalanUzrast;
    static int napravljeniNovogodisnjiPaketici;
public:
    NovogodisnjiPaketic () : Paketic() {
        minimalanUzrast = 4;
        status = NAPRAVLJEN;
        if (status == NAPRAVLJEN)
            napravljeniNovogodisnjiPaketici++;
    }

    NovogodisnjiPaketic (const DinString& o, const Dete& d, int mu) : Paketic(o, d), minimalanUzrast(mu) {
        status = NAPRAVLJEN;
        if (status == NAPRAVLJEN)
            napravljeniNovogodisnjiPaketici++;
    }

    ~NovogodisnjiPaketic () {
        if (status == NAPRAVLJEN)
            --napravljeniNovogodisnjiPaketici;
    }

    int getMinimalanUzrast () const {
        return minimalanUzrast;
    }

    int getNapravljeniNovogodisnjiPaketici () const {
        return napravljeniNovogodisnjiPaketici;
    }

    bool isporuci () {
        if (!spakuj() || !namenjen.getZasluzenNovogodisnjiPaketic()) {
            cout << "Novogodisnji paketic ne moze biti isporucen!" << endl;
            return false;
        }
        cout << "Novogodisnji paketic ce uskoro biti isporucen. Primalac je " << namenjen.getNadimak() << "." << endl;
        status = ISPORUCEN;
        return true;
    }

    void ispisi () const {
        cout << "--- Novogodisnji paketic ---" << endl;
        cout << "Minimalan uzrast: " << minimalanUzrast << endl;
        cout << "Paket je za: " << endl << namenjen << endl;
        cout << "Opis paketica: " << opis << endl;
        cout << "Paketic je u stanju: ";
        switch (status) {
            case NAPRAVLJEN: cout << "NAPRAVLJEN"; break;
            case SPAKOVAN: cout << "SPAKOVAN"; break;
            case ISPORUCEN: cout << "ISPORUCEN"; break;
        }
        cout << endl;
    }
};

int NovogodisnjiPaketic::napravljeniNovogodisnjiPaketici = 0;

#endif // NOVOGODISNJIPAKETIC_HPP_INCLUDED
