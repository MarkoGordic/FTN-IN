#ifndef COMPONENT_HPP_INCLUDED
#define COMPONENT_HPP_INCLUDED

class Component {
protected:
    double X, Y;
public:
    double getX () const { return X; }

    double getY () const { return Y; }

    virtual void printComponent () const {
        cout << "Coordinates: (" << X << "," << Y << ")" << endl;
    }

    virtual DinString getTypeName () const = 0;
};

#endif // COMPONENT_HPP_INCLUDED
