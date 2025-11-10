#ifndef CHECKBOX_HPP_INCLUDED
#define CHECKBOX_HPP_INCLUDED

#include "component.hpp"

class CheckBox : public Component {
    private:
        bool pressed;
        static DinString typeName;

    public:
        CheckBox(int X = 0, int Y = 0, int pressed = false) {
            this -> X = X;
            this -> Y = Y;
            this -> pressed = pressed;
        }

        DinString getTypeName() const {
            return typeName;
        }

        void printComponent() const {
            cout << getTypeName() << endl;
            Component::printComponent();
            cout << " CB pressed = " << pressed;
        }

        bool getPressed() const {
            return pressed;
        }

        void setPressed(bool pressed) {
            this -> pressed = pressed;
        }

};


DinString CheckBox::typeName = "CheckBox";

#endif // CHECKBOX_HPP_INCLUDED
