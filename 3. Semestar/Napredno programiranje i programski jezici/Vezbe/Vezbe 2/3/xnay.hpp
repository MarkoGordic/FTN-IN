#ifndef XNAY_HPP_INCLUDED
#define XNAY_HPP_INCLUDED

class XnaY{
private:
    int x;
    int y;

public:
    XnaY();
    XnaY(int, int);
    XnaY(const XnaY &);

    void setX(int);
    void setY(int);
    void setX_Y(int, int);

    int getX() const;
    int getY() const;
    double getXnaY() const;
};

#endif // XNAY_HPP_INCLUDED