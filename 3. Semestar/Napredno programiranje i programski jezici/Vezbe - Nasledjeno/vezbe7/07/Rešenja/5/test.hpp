#ifndef TEST_HPP_INCLUDED
#define TEST_HPP_INCLUDED

#include <iostream>
using namespace std;
#include "dinstring.hpp"

class Test{
    protected:
        DinString naziv;
        int osvojeniPoeni;

    public:
        Test(const char* d = "", int os = 0) : naziv(d), osvojeniPoeni(os) {}

        virtual int getPoeni() const = 0;
        virtual bool polozio() const = 0;

        void ispis() const{
            cout << "Naziv: " << naziv << " ; Osvojeni poeni: " << osvojeniPoeni << endl;
        }
};

#endif // TEST_HPP_INCLUDED
