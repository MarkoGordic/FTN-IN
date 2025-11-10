#ifndef KRUG_HPP_INCLUDED
#define KRUG_HPP_INCLUDED

class Krug : public Elipsa {
public:
    Krug () : Elipsa (2, 2) {}
    Krug (double r) : Elipsa (r, r) {}
    Krug (const Krug& k) : Elipsa((Elipsa)k) {}
};

#endif // KRUG_HPP_INCLUDED
