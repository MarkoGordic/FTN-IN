#ifndef COMPUTER_HPP_INCLUDED
#define COMPUTER_HPP_INCLUDED

class Computer {
private:
    double hddGB, ramGB;
    DinString gCard, os;
public:
    Computer() : hddGB(0), ramGB(0) {}

    Computer(double h, double r, const char* s1, const char* s2)
        : hddGB(h), ramGB(r), gCard(s1), os(s2) {}

    Computer(const Computer& comp)
        : hddGB(comp.hddGB), ramGB(comp.ramGB), gCard(comp.gCard), os(comp.os) {}

    friend ostream& operator<<(ostream& out, const Computer& comp) {
        out << "My Computer" << endl;
        out << "HDD GB: " << comp.hddGB << endl;
        out << "RAM GB: " << comp.ramGB << endl;
        out << "Graphics Card: " << comp.gCard << endl;
        out << "OS: " << comp.os << endl;
        return out;
    }
};

#endif // COMPUTER_HPP_INCLUDED
