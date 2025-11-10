#ifndef TELEFON_H_INCLUDED
#define TELEFON_H_INCLUDED

#include "dinstring.hpp"
#include <iostream>
using namespace std;

class Telefon
{
    protected:
        DinString broj;

    public:
        Telefon() : broj("22-333") {}

        Telefon(DinString br) : broj(br) {}

        bool pozovi(DinString br)
        {
        bool ret = false;
            if (br != broj)
            {
            	return true;
            }
            return ret;
        }
};

#endif // TELEFON_H_INCLUDED
