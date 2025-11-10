#ifndef XNAY_HPP_INCLUDED
#define XNAY_HPP_INCLUDED


#include <iostream>
#include <cmath> // zbog funkcije pow

using namespace std;

class XnaY
{
private:
    int x,y;
public:
    XnaY()
    {
        x = 1;
        y = 1;
    }

    XnaY(int xx, int yy)
    {
        x = xx;
        y = yy;
    }

    XnaY(const XnaY &xy)
    {
        x = xy.x;
        y = xy.y;
    }

    void setX(int xx)
    {
        x = xx;
    }

    void setY(int yy)
    {
        y = yy;
    }

    void setX_Y(int xx, int yy)
    {
        x = xx;
        y = yy;
    }

    int getX() const
    {
        return x;
    }

    int getY() const
    {
        return y;
    }

    double getXnaY() const
    {
        return pow(x, y);
    }

};

#endif // XNAY_HPP_INCLUDED
