#ifndef KOCKA_HPP_INCLUDED
#define KOCKA_HPP_INCLUDED
#include <cstdlib>

class Kocka{

private:
    int vrednost;

public:
    Kocka();

    Kocka(int);

    Kocka(const Kocka&);

    void baci();

    int getVrednost() const;
};

#endif // KOCKA_HPP_INCLUDED