#ifndef DETE_HPP_INCLUDED
#define DETE_HPP_INCLUDED

enum Pol {DECAK, DEVOJCICA};

class Dete {
protected:
    DinString nadimak;
    Pol pol;
    int uzrast;
    bool zasluzenNovogodisnjiPaketic;
public:
    Dete () : nadimak("djole"), pol(DECAK), uzrast(6), zasluzenNovogodisnjiPaketic(false) {}

    Dete (const DinString& ime, Pol p, int u, bool zasluga)
        : nadimak(ime), pol(p), uzrast(u), zasluzenNovogodisnjiPaketic(zasluga) {}

    Dete (const Dete& d)
        : nadimak(d.nadimak), pol(d.pol), uzrast(d.uzrast), zasluzenNovogodisnjiPaketic(d.zasluzenNovogodisnjiPaketic) {}

    DinString getNadimak () const {
        return nadimak;
    }

    Pol getPol () const {
        return pol;
    }

    int getUzrast () const {
        return uzrast;
    }

    bool getZasluzenNovogodisnjiPaketic () const {
        return zasluzenNovogodisnjiPaketic;
    }

    friend ostream& operator<<(ostream& out, const Dete& dete) {
        out << "Dete" << endl;
        out << "Nadimak: " << dete.nadimak << endl;
        out << "Pol: " << (dete.pol == DECAK ? "DECAK" : "DEVOJCICA") << endl;
        out << "Uzrast: " << dete.uzrast << endl;
        out << "Zasluzen Novogodisnji Paketic: " << (dete.zasluzenNovogodisnjiPaketic ? "DA" : "NE") << endl;
        return out;
    }
};

#endif // DETE_HPP_INCLUDED
