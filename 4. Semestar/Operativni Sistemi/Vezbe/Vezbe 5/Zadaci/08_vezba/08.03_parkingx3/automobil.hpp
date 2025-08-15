#ifndef AUTOMOBIL_HPP_INCLUDED
#define AUTOMOBIL_HPP_INCLUDED

#include <iostream>

using namespace std;

class Automobil {
public:
    // rbr  - Redni broj automobila
    // ulaz - Ulaz na koji automobil pokusava da udje
    void ceka(int rbr, int ulaz) {
        cout << "Automobil "<< rbr <<" ceka kako bi usao na parking, na ulazu "<< ulaz <<endl;
    }

    // rbr  - Redni broj automobila
    void zauzima(int rbr) {
        cout << "Automobil " << rbr <<" je zauzeo parking." << endl;
    }

    // rbr  - Redni broj automobila
    void napusta(int rbr) {
        cout << "Automobil "<< rbr << " je napustio parking." << endl;
    }
};

#endif // AUTOMOBIL_HPP_INCLUDED
