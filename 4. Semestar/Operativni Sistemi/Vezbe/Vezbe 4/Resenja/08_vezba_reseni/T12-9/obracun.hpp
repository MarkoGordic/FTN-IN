#ifndef OBRACUN_HPP
#define OBRACUN_HPP

#include <string>
#include <map>
#include <list>

using namespace std;

void obracunajUkupno(list<string> kupljeno, map<string, double> cenovnik, double& ukupno)
{
    // Ne zna se da li je vrednost za ukupno inicijalizovana pre poziva funkcije
    ukupno = 0;
    for (auto it = kupljeno.begin(); it != kupljeno.end(); ++it) {
        ukupno += cenovnik[*it];
    }
}

#endif // OBRACUN_HPP
