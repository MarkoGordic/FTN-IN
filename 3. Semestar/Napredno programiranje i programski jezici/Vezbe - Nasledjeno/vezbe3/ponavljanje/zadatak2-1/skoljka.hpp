#ifndef SKOLJKA_HPP_INCLUDED
#define SKOLJKA_HPP_INCLUDED

enum Boja {PLAVA, CRVENA, ZELENA};

class Skoljka {
private:
    Boja boja;
public:
    Skoljka () {
        boja = PLAVA;
    }

    Skoljka (Boja b) {
        boja = b;
    }

    Skoljka (const Skoljka& s) {
        boja = s.boja;
    }

    void setBoja (Boja b) {
        boja = b;
    }

    Boja getBoja () const {
        return boja;
    }

    friend void ispisSkoljka (const Skoljka& s);
};

#endif // SKOLJKA_HPP_INCLUDED
