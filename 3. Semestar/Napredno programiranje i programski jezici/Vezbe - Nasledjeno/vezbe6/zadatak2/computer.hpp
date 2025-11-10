#ifndef COMPUTER_HPP_INCLUDED
#define COMPUTER_HPP_INCLUDED

class Computer {
private:
    double hddGB;
    double ramGB;
    DinString gCard;
    DinString os;
public:
    Computer () : hddGB(128), ramGB(8), gCard("amd"), os("vindoza") {}
    Computer (double hdd, double ram, const char gcard[], const char o[]) :
        hddGB(hdd), ramGB(ram), gCard(gcard), os(o) {}

    Computer (const Computer& c) :
        hddGB(c.hddGB), ramGB(c.ramGB), gCard(c.gCard), os(c.os) {}

    friend ostream& operator<<(ostream &out, const Computer& c) {
        out << "\nComputer" << endl;
        out << "hddGB: " << c.hddGB << endl;
        out << "ramGB: " << c.ramGB << endl;
        out << "gCard: " << c.gCard << endl;
        out << "os: " << c.os << endl;
        out << endl;
        return out;
    }

};

#endif // COMPUTER_HPP_INCLUDED
