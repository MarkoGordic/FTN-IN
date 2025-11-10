#ifndef XNAY_HPP_INCLUDED
#define XNAY_HPP_INCLUDED

class XnaY{
private:
    int x, y;
public:
    XnaY();
    XnaY(int xx, int yy);
    XnaY(const XnaY& xnay);

    void setX(int xx);
    void setY(int yy);
    void setX_Y(int xx, int yy);

    int getX() const;
    int getY() const;
    double getXnaY() const;
};

#endif // XNAY_HPP_INCLUDED
