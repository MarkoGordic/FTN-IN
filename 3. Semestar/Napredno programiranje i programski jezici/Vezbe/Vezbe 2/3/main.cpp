#include <iostream>
using namespace std;

#include "xnay.hpp"

int main(){
    XnaY xnay;
    int x, y;

    cout << "Unesite x: ";
    cin >> x;
    cout << "Unesite y: ";
    cin >> y;

    xnay.setX_Y(x, y);

    cout << "x na y je: " << xnay.getXnaY() << endl;

    return 0;
}