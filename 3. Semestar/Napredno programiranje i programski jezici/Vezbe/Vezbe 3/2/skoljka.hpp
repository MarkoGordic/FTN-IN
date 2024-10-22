#ifndef SKOLJKA_HPP_INCLUDED
#define SKOLJKA_HPP_INCLUDED

enum BojaSkoljke {PLAVA, CRVENA, ZELENA};

class Skoljka {
private:
    BojaSkoljke boja;

public:
    Skoljka(){
        boja = PLAVA;
    };

    void setBoja(BojaSkoljke b){
        boja = b;
    }

    BojaSkoljke getBoja()const{
        return boja;
    }
};

#endif // SKOLJKA_HPP_INCLUDED