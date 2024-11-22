#ifndef FOTOAPARAT_HPP_INCLUDED
#define FOTOAPARAT_HPP_INCLUDED

#include <iostream>
using namespace std;

template <int brojFotografijaPoJednomPunjenju>
class Fotoaparat {
protected:
    int brojPreostalihFotografija;
    bool ukljucen;
public:
    Fotoaparat() : brojPreostalihFotografija(brojFotografijaPoJednomPunjenju), ukljucen(false) {}

    bool ukljuci() {
        if(ukljucen){
            cout << "Fotoaparat je vec ukljucen" << endl;
            return false;
        }

        ukljucen = true;
        cout << "Fotoaparat uspesno ukljucen" << endl;
        return true;
    }

    bool iskljuci() {
        if(!ukljucen){
            cout << "Fotoaparat je vec iskljucen" << endl;
            return false;
        }

        ukljucen = false;
        cout << "Fotoaparat uspesno iskljucen" << endl;
        return true;
    }

    bool napuniFotoaparat(int brojFotografija) {
        if(brojFotografija < 0){
            cout << "Ne mozete napuniti fotoaparat sa negativnim brojem fotografija" << endl;
            return false;
        }

        if(brojFotografija > brojFotografijaPoJednomPunjenju){
            cout << "Ne mozete napuniti fotoaparat sa vise fotografija nego sto moze stati" << endl;
            return false;
        }

        brojPreostalihFotografija = brojFotografija;
        cout << "Fotoaparat uspesno napunjen" << endl;
        return true;
    }

    bool snimiFotografiju() {
        if(!ukljucen){
            cout << "Fotoaparat nije ukljucen" << endl;
            return false;
        }

        if(brojPreostalihFotografija == 0){
            cout << "Nema dovoljno slobodnog prostora za fotografiju" << endl;
            return false;
        }

        brojPreostalihFotografija--;
        cout << "Fotografija uspesno snimljena" << endl;
        return true;
    }

    void punjenjeNaMax() {
        brojPreostalihFotografija = brojFotografijaPoJednomPunjenju;
        cout << "Fotoaparat uspesno napunjen na max" << endl;
    }
};

#endif // FOTOAPARAT_HPP_INCLUDED