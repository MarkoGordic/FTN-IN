#include "xnay.hpp"
#include <cmath>

XnaY::XnaY(){
    x = 1;
    y = 1;
}

XnaY::XnaY(int xx, int yy){
    x = xx;
    y = yy;
}

XnaY::XnaY(const XnaY& xnay){
    x = xnay.x;
    y = xnay.y;
}

void XnaY::setX(int xx){
    x = xx;
}

void XnaY::setY(int yy){
    y = yy;
}

void XnaY::setX_Y(int xx, int yy){
    x = xx; // setX(xx)
    y = yy; // setY(yy)
}

int XnaY::getX() const {
    return x;
}

int XnaY::getY() const {
    return y;
}

double XnaY::getXnaY() const {
    return pow(x, y);
}
