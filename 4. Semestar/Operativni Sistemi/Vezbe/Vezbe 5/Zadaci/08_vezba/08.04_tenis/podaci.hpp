#ifndef PODACI_HPP_INCLUDED
#define PODACI_HPP_INCLUDED

using namespace std;
using namespace chrono;

struct Podaci {
    duration<double, milli> trajanje;
    system_clock::time_point dosao;
    system_clock::time_point pocetak;
};

#endif // PODACI_HPP_INCLUDED
