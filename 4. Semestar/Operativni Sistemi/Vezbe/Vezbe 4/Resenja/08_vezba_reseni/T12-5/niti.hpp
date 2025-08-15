#ifndef NITI_HPP
#define NITI_HPP

#include <thread>
#include <map>

#include "recnik.hpp"

using namespace std;

// Implementacija pokretanja dodatne niti koja treba da napravi novi rečnik (koristeći funkciju "napraviRecnik")
map<string, string> izracunaj(map<string, string> engSrp)
{
    map<string, string> srpEng;
    thread t(napraviRecnik, ref(engSrp), ref(srpEng)); // engSrp se moze proslediti po referenci iako u funkciji napraviRecnik nije eksplicitno receno da se ocekuje referenca, na ovaj nacin ce se izbeci kreiranje kopije cele mape, a to moze poboljsati performanse programa
    t.join();
    return srpEng;
}

#endif // NITI_HPP
