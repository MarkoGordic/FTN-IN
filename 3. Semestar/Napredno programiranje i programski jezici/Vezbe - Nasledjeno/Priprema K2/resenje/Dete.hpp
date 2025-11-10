#ifndef DETE_HPP_INCLUDED
#define DETE_HPP_INCLUDED

#include "dinstring.hpp"

enum Pol {DECAK, DEVOJCICA};

class Dete {
    private:
        DinString nadimak;
        Pol pol;
        int uzrast;
        bool zasluzenNovogodisnjiPaketic;

    public:
        Dete() : nadimak(""), pol(DECAK), uzrast(3), zasluzenNovogodisnjiPaketic(true) {}
        Dete(const DinString& n, Pol p, int u, bool znp) : nadimak(n), pol(p), uzrast(u), zasluzenNovogodisnjiPaketic(znp) {}
        Dete(const Dete& d) : nadimak(d.nadimak), pol(d.pol), uzrast(d.uzrast), zasluzenNovogodisnjiPaketic(d.zasluzenNovogodisnjiPaketic) {}

        DinString getNadimak() const { return nadimak; }
        Pol getPol() const { return pol; }
        int getUzrast() const { return uzrast; }
        bool getZasluzenNovogodisnjiPaketic() const { return zasluzenNovogodisnjiPaketic; }

        friend ostream& operator<<(ostream& o, const Dete& d) {
            o << "\tnadimak: " << d.nadimak << endl;

            switch(d.pol) {
                case DECAK:
                    o << "\tpol: decak" << endl;
                    break;
                case DEVOJCICA:
                    o << "\tpol: devojcica" << endl;
                    break;
                default:
                    o << "\tpol: nepoznat" << endl;
            }

            o << "\tuzrast: " << d.uzrast << endl;

            if(d.zasluzenNovogodisnjiPaketic)
                o << "\tzasluzen novogodisnji paketic: da" << endl;
            else
                o << "\tzasluzen novogodisnji paketic: ne" << endl;

            return o;
        }
};

#endif // DETE_HPP_INCLUDED
