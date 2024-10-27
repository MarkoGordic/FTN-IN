#ifndef DUH_HPP_INCLUDED
#define DUH_HPP_INCLUDED

#include <cstdlib>
#include <iostream>
#include "Lovac.hpp"
using namespace std;

enum StatusDuh{
    AKTIVAN,
    UHVACEN
};

class Duh {
private:
    int snaga;
    StatusDuh status;

public:
    Duh(){
        snaga = rand() % 21;
        status = AKTIVAN;
    }

    Duh(int snaga){
        this->snaga = snaga;
        this->status = AKTIVAN;
    }

    bool napadniLovca(Lovac &lovac){
        return lovac.smanjiSnagu(snaga);
    }

    void ispisi() const {
        cout << "Duh snaga: " << snaga << endl;
        cout << "Duh status: " << (status == AKTIVAN ? "Aktivan" : "Uhvacen") << endl;
    }

    int getSnaga(){
        return snaga;
    }

    StatusDuh getStatus(){
        return status;
    }

    void setSnaga(int snaga){
        this->snaga = snaga;
    }

    void setStatus(StatusDuh status){
        this->status = status;
    }
};

#endif // DUH_HPP_INCLUDED