#ifndef COMPONENT_HPP_INCLUDED
#define COMPONENT_HPP_INCLUDED

#include "dinstring.hpp"

class Component {
    protected:
        int X;
        int Y;

    public:
        double getX() const { return X; }
        double getY() const { return Y; }

        virtual void printComponent() const {
            cout << "Component: X = " << X << ", Y = " << Y;
        }

        virtual DinString getTypeName() const = 0;
};


#endif // COMPONENT_HPP_INCLUDED
