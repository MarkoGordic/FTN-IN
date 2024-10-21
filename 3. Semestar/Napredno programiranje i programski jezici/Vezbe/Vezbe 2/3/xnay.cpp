#include "xnay.hpp"
#include <cmath>

XnaY::XnaY() {
    x = 1;
    y = 1;
}

XnaY::XnaY(int x, int y) {
    this->x = x;
    this->y = y;
}

XnaY::XnaY(const XnaY &xnay) {
    x = xnay.x;
    y = xnay.y;
}

void XnaY::setX(int x) {
    this->x = x;
}

void XnaY::setY(int y) {
    this->y = y;
}

void XnaY::setX_Y(int x, int y) {
    this->x = x;
    this->y = y;
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