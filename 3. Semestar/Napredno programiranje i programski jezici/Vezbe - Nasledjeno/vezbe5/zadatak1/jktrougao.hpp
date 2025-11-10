#ifndef JKTROUGAO_HPP_INCLUDED
#define JKTROUGAO_HPP_INCLUDED

class JKTrougao : public Trougao {
public:
    JKTrougao () : Trougao (2, 3, 3) {}
    JKTrougao (double aa, double bb) : Trougao (aa, bb, bb) {}
    JKTrougao (const JKTrougao& jkt) : Trougao (jkt.a, jkt.b, jkt.c) {}         // smemo ovo jer su polja protected u klasi Trougao
                                                                                // da su private -> koristili bismo get
                                                                                // moglo je i Trougao(jkt) kao konstruktor kopije
    // redefinisemo setere iz klase Trougao
    void setB (double bb) {
        b = bb;
        c = bb;
    }

    // neophodno je oba redefinisati kako bismo imali JKK trougao
    void setC (double cc) {
        b = cc;
        c = cc;
    }
};

#endif // JKTROUGAO_HPP_INCLUDED
