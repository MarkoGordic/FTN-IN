#ifndef IGRAC_HPP_INCLUDED
#define IGRAC_HPP_INCLUDED

#include <iostream>
using namespace std;

class Igrac {
private:
    int poeni;
    int brojPartija;

public:
    Igrac(int p = 0, int bp = 0){
        poeni = p;
        brojPartija = bp;
    }

    void dodajPoene(int p){
        poeni += p;
    }

    void odigrajPartiju(){
        brojPartija++;
    }

    void resetuj(){
        poeni = 0;
        brojPartija = 0;
    }

    void ispis()const{
        cout << "Poeni: " << poeni << endl;
        cout << "Broj partija: " << brojPartija << endl;    
    }

    int getPoeni()const{
        return poeni;
    }

    int getBrojPartija()const{
        return brojPartija;
    }

    void setPoeni(int p){
        poeni = p;
    }
};

#endif // IGRAC_HPP_INCLUDED