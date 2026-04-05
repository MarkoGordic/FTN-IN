#ifndef AUTOMOBIL_H_INCLUDED
#define AUTOMOBIL_H_INCLUDED

#include <iostream>

using namespace std;

class Automobil {
public:
    // rbr - Redni broj automobila
    void ceka(int rbr) {
        cout << "Automobil " << rbr << " ceka jer je parking zauzet." << endl;
    }

    // rbr - Redni broj automobila
    void parkira(int rbr) {
        cout << "Automobil " << rbr << " stupa na parking." << endl;
    }

    // rbr - Redni broj automobila
    void napusta(int rbr) {
        cout << "Automobil " << rbr << " je izasao sa parkinga." << endl;
    }
};

#endif // AUTOMOBIL_H_INCLUDED
