#include "XnaY.hpp"

int main()
{
    // testiranje sva tri konstruktora
    XnaY xy1;
    XnaY xy2(5,2);
    XnaY xy3(xy2);


    cout <<  "xy1: X = " << xy1.getX() << "; Y = " << xy1.getY() << "; X^Y = " << xy1.getXnaY() << endl;
    cout <<  "xy2: X = " << xy2.getX() << "; Y = " << xy2.getY() << "; X^Y = " << xy2.getXnaY() << endl;
    cout <<  "xy3: X = " << xy3.getX() << "; Y = " << xy3.getY() << "; X^Y = " << xy3.getXnaY() << endl;


    int x, y;
    cout << endl << "Unesite ceo broj x: ";
    cin >> x;
    cout << endl << "Unesite ceo broj y: ";
    cin >> y;

    xy1.setX(x);
    xy1.setY(y);
    cout <<  "xy1: X = " << xy1.getX() << "; Y = " << xy1.getY() << "; X^Y = " << xy1.getXnaY() << endl;

    xy2.setX_Y(x, y);
    cout <<  "xy2: X = " << xy2.getX() << "; Y = " << xy2.getY() << "; X^Y = " << xy2.getXnaY() << endl;

    return 0;
}
