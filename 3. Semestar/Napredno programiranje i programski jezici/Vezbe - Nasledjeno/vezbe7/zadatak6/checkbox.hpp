#ifndef CHECKBOX_HPP_INCLUDED
#define CHECKBOX_HPP_INCLUDED

class CheckBox : public Component {
private:
    bool pressed;
    static DinString typeName;
public:
    CheckBox () {   /// NE MOZEMO U INICIJALIZATORU POSTAVITI VREDNOST ZA POLJA X I Y
        this -> X = 0;
        this -> Y = 0;
        this -> pressed = false;
    }

    CheckBox (int X, int Y, int pressed) {
        this -> X = X;
        this -> Y = Y;
        this -> pressed = pressed;
    }

    DinString getTypeName () const {
        return typeName;
    }

    bool getPressed () const {
        return pressed;
    }

    void setPressed (bool pressed) {
        this->pressed = pressed;
    }

    void printComponent () const {
        cout << "Component: " << typeName << endl;
        Component::printComponent();
        cout << "Pressed: " << (pressed ? "True" : "False") << endl;
    }
};

DinString CheckBox::typeName = "CheckBox";

#endif // CHECKBOX_HPP_INCLUDED
