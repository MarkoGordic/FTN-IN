#ifndef OBLIK_HPP_INCLUDED
#define OBLIK_HPP_INCLUDED

class Oblik {
protected:
    Pravougaonik A;
    Elipsa B;
public:
    Oblik () : A(3, 4), B(1.5, 2) {}
    Oblik (double a, double b) : A(a, b), B(a / 2, b / 2) {}
    Oblik (const Oblik& oblik) : A(oblik.A), B(oblik.B) {}

    double getP () const {
        return A.getP() - B.getP();
    }

    double getO () const {
        return A.getO() + B.getO();
    }
};

#endif // OBLIK_HPP_INCLUDED
