#ifndef JSTROUGAO_HPP_INCLUDED
#define JSTROUGAO_HPP_INCLUDED

class JSTrougao : public JKTrougao {
public:
    // kod nasledjivanja se ne nasledjuju konstruktori i destruktori!!!
    JSTrougao () : JKTrougao(2, 2) {}
    JSTrougao (double a) : JKTrougao(a, a) {}
    JSTrougao (const JSTrougao& jst) : JKTrougao((JKTrougao)jst) {}         // potrebno je i odraditi konverziju tipa

    void setA (double aa) {
        a = aa;
        b = aa;
        c = aa;
    }

    void setB (double bb) {
        a = bb;
        b = bb;
        c = bb;
    }

    void setC (double cc) {
        a = cc;
        b = cc;
        c = cc;
    }
};

#endif // JSTROUGAO_HPP_INCLUDED
