#ifndef JKTROUGAO_HPP_INCLUDED
#define JKTROUGAO_HPP_INCLUDED

#include "Trougao.hpp"

class JKTrougao : public Trougao {
public:
    JKTrougao() : Trougao(4,4,2){}
    JKTrougao(double aa, double bb) : Trougao(aa,bb,bb){}
    JKTrougao(const JKTrougao &jkt) : Trougao(jkt.a,jkt.b,jkt.c){}
    
    void setB(double bb){
        b = bb;
        c = bb;
    }

    void setC(double cc){
        b = cc;
        c = cc;
    }
};

#endif // JKTROUGAO_HPP_INCLUDED