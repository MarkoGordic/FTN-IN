#ifndef COMPUTER_HPP_INCLUDED
#define COMPUTER_HPP_INCLUDED

#include "dinstring.hpp"

class Computer {
protected:
    double hddGB;
    double ramGB;
    DinString gCard;
    DinString os;
public:
    Computer() : hddGB(0), ramGB(0), gCard(), os() {}
    Computer(double hddGB, double ramGB, const char* gCard, const char* os) : hddGB(hddGB), ramGB(ramGB), gCard(gCard), os(os) {}
    Computer(const Computer& c) : hddGB(c.hddGB), ramGB(c.ramGB), gCard(c.gCard), os(c.os) {}

    friend std::ostream& operator<<(std::ostream& out, const Computer& c){
        out << "HDD: " << c.hddGB << "GB, RAM: " << c.ramGB << "GB, Graficka: " << c.gCard << ", OS: " << c.os;
        return out;
    }
};

#endif // COMPUTER_HPP_INCLUDED