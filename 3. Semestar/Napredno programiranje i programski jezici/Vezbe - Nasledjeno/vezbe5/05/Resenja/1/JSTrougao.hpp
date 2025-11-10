#ifndef JSTROUGAO_HPP_INCLUDED
#define JSTROUGAO_HPP_INCLUDED

#include "JKTrougao.hpp"

class JSTrougao : public JKTrougao {
    public:
        JSTrougao() : JKTrougao(1, 1) {}
        JSTrougao(double aa) : JKTrougao(aa, aa) {}
        JSTrougao(const JSTrougao &jst) : JKTrougao(jst.a, jst.b) {}
};

#endif // JSTROUGAO_HPP_INCLUDED
