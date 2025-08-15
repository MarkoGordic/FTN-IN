#ifndef AUTOMOBIL_HPP_INCLUDED
#define AUTOMOBIL_HPP_INCLUDED

#include <iostream>
#include <mutex>

using namespace std;

class Automobil {
private:
    mutex terminal;
public:
    // rbr - Redni broj automobila
    void ceka(int rbr) {
        unique_lock<mutex> u(terminal);
        cout << "Automobil " << rbr << " ceka jer je parking zauzet." << endl;
    }

    // rbr - Redni broj automobila
    void parkira(int rbr) {
        unique_lock<mutex> u(terminal);
        cout << "Automobil " << rbr << " stupa na parking." << endl;
    }

    // rbr - Redni broj automobila
    void napusta(int rbr) {
        unique_lock<mutex> u(terminal);
        cout << "Automobil " << rbr << " je izasao sa parkinga." << endl;
    }
};

#endif // AUTOMOBIL_HPP_INCLUDED
