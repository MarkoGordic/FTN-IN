#include "artikal.hpp"

int Artikal::instanci = 0; // mora van klase

Artikal::Artikal(const char n[], const double c) : naziv(n), cena(c){
    instanci++;
}

Artikal::Artikal(const DinString& n, const double c) : naziv(n), cena(c){
    instanci++;
}

Artikal::Artikal(const Artikal& a) : naziv(a.naziv), cena(a.cena){
    instanci++;
}

Artikal::~Artikal(){
    instanci--;
}

ostream& operator<<(ostream& os, const Artikal& a){
    os << "--------- ARTIKAL ------" << endl;
    os << setw(10)<<"NAZIV: " << a.naziv << endl;
    os << setw(10)<<"CENA: " << a.cena << endl;
    os << setw(10)<<"INSTANCI: " << a.instanci << endl;
    os << "------------------------" << endl << endl;

    return os;
}
