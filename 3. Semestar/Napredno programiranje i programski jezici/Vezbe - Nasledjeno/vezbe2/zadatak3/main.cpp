#include <iostream>

using namespace std;

#include "xnay.hpp"

int main()
{
    XnaY obj1;
    XnaY obj2(2, 2);
    XnaY obj3(obj2);

    cout << obj1.getX() << endl;
    cout << obj1.getY() << endl;
    cout << obj1.getXnaY() << endl;

    obj1.setX(2);
    obj1.setY(3);
    cout << obj1.getX() << endl;
    cout << obj1.getY() << endl;
    cout << obj1.getXnaY() << endl;

    obj1.setX_Y(4, 5);
    cout << obj1.getX() << endl;
    cout << obj1.getY() << endl;
    cout << obj1.getXnaY() << endl;
    return 0;
}
