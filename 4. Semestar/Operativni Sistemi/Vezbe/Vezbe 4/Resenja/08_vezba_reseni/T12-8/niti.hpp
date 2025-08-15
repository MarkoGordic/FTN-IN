#ifndef NITI_HPP
#define NITI_HPP

#include <thread>

#include "cenovnik.hpp"

using namespace std;

map<string, double> izracunaj(map<string, double>& a, map<string, double>& b)
{
    map<string, double> c;
    thread t(nadjiPovoljno, a, b, ref(c));
    t.join();
    return c;
}

#endif // NITI_HPP
