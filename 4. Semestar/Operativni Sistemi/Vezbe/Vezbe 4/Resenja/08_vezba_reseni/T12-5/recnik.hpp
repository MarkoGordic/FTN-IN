#ifndef RECNIK_HPP
#define RECNIK_HPP

#include <map>
#include <string>

using namespace std;

// Funkcija koja će biti iskorišćena kao funkcija niti - od zadatog englesko-srpskog rečnika ona pravi obrnuti rečnik - srpsko-engleski
//
// engSrp - Englesko-srpski rečnik (ključ je reč na engleskom, podatak je njen prevod na srpski)
// srpEng - Srpsko-engleski rečnik (ključ je reč na srpskom, podatak je njen prevod na engleski) - ovaj parametar treba da se popuni izvršenjem ove funkcije
//
void napraviRecnik(map<string, string> engSrp, map<string, string>& srpEng)
{
    for (auto it = engSrp.begin(); it != engSrp.end(); ++it) {
        string kljuc = it->first;
        string vrednost = it->second;
        srpEng[vrednost] = kljuc;
    }
}


#endif // RECNIK_HPP
