#ifndef ZAGLAVLJE_H_INCLUDED
#define ZAGLAVLJE_H_INCLUDED

#include <iostream>
#include <cmath> // zbog funkcije pow

using namespace std;

class XnaY {
    private:
        int x,y;
    public:
        //PROTOTIPOVI
        XnaY();
        XnaY(int, int);
        XnaY(const XnaY&);

        // set metode
        void setX(int);
        void setY(int);
        void setX_Y(int,int);

        // get metode
        int getX() const;
        int getY() const;
        double getXnaY() const;
};

#endif // ZAGLAVLJE_H_INCLUDED
