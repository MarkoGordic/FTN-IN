#ifndef IGRAC_HPP_INCLUDED
#define IGRAC_HPP_INCLUDED

#include <iostream>
using namespace std;

class Igrac{
private:
    int poeni;
    int brojPartija;
public:
    Igrac(int p = 0, int bp = 0){
        poeni = p;
        brojPartija = bp;
    }

    Igrac(const Igrac&i){
        poeni = i.poeni;
        brojPartija = i.brojPartija;
    }

    int getPoeni()const{
        return poeni;
    }

    int getBrojPartija()const{
        return brojPartija;
    }

    void dodajPoene(int x){
        poeni +=x;
    }

    void odigrajPartiju(){
        brojPartija++;
    }

    void resetuj(){
        poeni = 0;
        brojPartija = 0;
    }

    void setPoeni(int p){
        poeni = p;
    }

    //metoda za ispis
    void ispis()const{
        cout<<"--- IGRAC ---"<<endl;
        cout<<"Broj poena: "<<poeni<<endl;
        cout<<"Broj partija: "<<brojPartija<<endl;
        cout<<"-------------"<<endl;
    }
};

#endif // IGRAC_HPP_INCLUDED
