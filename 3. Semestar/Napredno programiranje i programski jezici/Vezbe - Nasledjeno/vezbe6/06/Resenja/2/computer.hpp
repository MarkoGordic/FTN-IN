#ifndef COMPUTER_HPP_INCLUDED
#define COMPUTER_HPP_INCLUDED

#include <iostream>
using namespace std;

#include "dinstring.hpp"

class Computer{
    private:
        double hddGB;
        double ramGB;
        DinString gCard;
        DinString os;

    public:
        Computer();
        Computer(double, double, const char*, const char*);
        Computer(const Computer&);

        friend ostream& operator<<(ostream&, const Computer&);
};

#endif // COMPUTER_HPP_INCLUDED
