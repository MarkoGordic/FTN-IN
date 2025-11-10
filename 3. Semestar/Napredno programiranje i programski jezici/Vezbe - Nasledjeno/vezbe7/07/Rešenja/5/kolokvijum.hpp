#ifndef KOLOKVIJUM_HPP_INCLUDED
#define KOLOKVIJUM_HPP_INCLUDED

#include <cstdlib>
#include "test.hpp"

class Kolokvijum : public Test {
    public:
        Kolokvijum() : Test() {}
        Kolokvijum(const char* n) : Test(n, rand()%25 + 1) {}

        int getPoeni() const {
            return osvojeniPoeni;
        }

        bool polozio() const {
            return (osvojeniPoeni > 12);
        }
};



#endif // KOLOKVIJUM_HPP_INCLUDED
