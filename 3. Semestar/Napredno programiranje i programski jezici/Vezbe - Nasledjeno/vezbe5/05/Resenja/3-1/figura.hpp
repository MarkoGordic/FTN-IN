#ifndef FIGURA_DEF
#define FIGURA_DEF

#include <iostream>
#include <math.h>

using namespace std;

class Figura
{
    public:
        virtual double getO() const = 0;
        virtual double getP() const = 0;
};

#endif
