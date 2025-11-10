#include "computer.hpp"

Computer::Computer():gCard("Nvidia GeForce GTX 970 or equal"), os("Win7")
{
    hddGB = 500;
    ramGB = 8;
}

Computer::Computer(double h, double r, const char* g, const char* o):gCard(g), os(o)
{
    hddGB = h;
    ramGB = r;

}

Computer::Computer(const Computer& c):gCard(c.gCard), os(c.os)
{
    hddGB = c.hddGB;
    ramGB = c.ramGB;
}

ostream& operator<<(ostream &out, const Computer &c)
{
    out << "HDD [GB]: " << c.hddGB << endl;
    out << "RAM [GB]: " << c.ramGB << endl;
    out << "Graphical card: " << c.gCard << endl;
    out << "Operative system: " << c.os << endl;
    return out;

}

