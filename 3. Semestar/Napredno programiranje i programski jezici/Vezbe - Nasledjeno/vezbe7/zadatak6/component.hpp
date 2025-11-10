#ifndef COMPONENT_HPP_INCLUDED
#define COMPONENT_HPP_INCLUDED

class Component {
protected:
    double X;
    double Y;
public:
    double getX () const {
        return X;
    }

    double getY () const {
        return Y;
    }

    virtual void printComponent () const {
        cout << "Koordinate" << endl;
        cout << "X = " << X << endl;
        cout << "Y = " << Y << endl;
    }

    virtual DinString getTypeName () const = 0;
};

#endif // COMPONENT_HPP_INCLUDED
