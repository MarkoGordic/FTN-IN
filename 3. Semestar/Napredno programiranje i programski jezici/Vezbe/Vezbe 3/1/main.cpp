#include <iostream>
using namespace std;

#include "valjak.hpp"

int main(){
    Valjak v(2, 4);
    cout << "R: " << v.getR() << endl;
    cout << "H: " << v.getH() << endl;
    cout << "V: " << v.getV() << endl;
    cout << "P: " << v.getP() << endl;

    return 0;
}