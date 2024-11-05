#ifndef JSTROUGAO_HPP_INCLUDED
#define JSTROUGAO_HPP_INCLUDED

#include "JKTrougao.hpp"

class JSTrougao : public JKTrougao {
public:
    JSTrougao() : JKTrougao(4,4){}
    JSTrougao(double aa) : JKTrougao(aa,aa){}
    JSTrougao(const JSTrougao &jst) : JKTrougao(jst.a,jst.b){}
    
    void setA(double aa){
        a = aa;
        b = aa;
        c = aa;
    }

    void setB(double bb){
        a = bb;
        b = bb;
        c = bb;
    }

    void setC(double cc){
        a = cc;
        b = cc;
        c = cc;
    }
};

#endif // JSTROUGAO_HPP_INCLUDED