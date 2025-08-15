#ifndef CENOVNIK_HPP
#define CENOVNIK_HPP

#include <string>
#include <map>

using namespace std;

void nadjiPovoljno(map<string, double> a, map<string, double> b, map<string, double> &jeftino)
{
    for (map<string, double>::const_iterator it = a.cbegin(); it != a.cend(); ++it) {
        jeftino[it->first] = min(it->second, b[it->first]);
    }
}

#endif // CENOVNIK_HPP
