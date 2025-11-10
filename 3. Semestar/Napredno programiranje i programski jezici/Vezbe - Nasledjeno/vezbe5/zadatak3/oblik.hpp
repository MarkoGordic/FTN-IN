#ifndef OBLIK_HPP_INCLUDED
#define OBLIK_HPP_INCLUDED

class Oblik {
private:
    Kvadrat A;
    Krug B;
public:
    Oblik () : A(1), B(0.5) {}
    Oblik (double aa) : A(aa), B(aa / 2) {}
    Oblik (const Oblik& o) : A(o.A), B(o.B) {}

    double getP () const {
        return A.getP() - B.getP();
    }

    double getO () const {
        return A.getO() + B.getO();
    }
};

#endif // OBLIK_HPP_INCLUDED
