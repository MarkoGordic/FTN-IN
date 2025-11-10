#ifndef PAKETIC_HPP_INCLUDED
#define PAKETIC_HPP_INCLUDED

#include "dinstring.hpp"
#include "Dete.hpp"

enum Status {NAPRAVLJEN, SPAKOVAN, ISPORUCEN};

class Paketic {
    protected:
        DinString opis;
        Dete namenjen;
        Status status;

    public:
        Paketic() : opis(""), namenjen(), status(NAPRAVLJEN) {}
        Paketic(const DinString& o, const Dete& d) : opis(o), namenjen(d), status(NAPRAVLJEN) {}

        Dete getNamenjen() const { return namenjen; }

        bool spakuj() {
            if(status == NAPRAVLJEN) {
                status = SPAKOVAN;
                return true;
            }

            return false;
        }

        virtual bool isporuci() = 0;
        virtual void ispisi() const = 0;
};

#endif // PAKETIC_HPP_INCLUDED
