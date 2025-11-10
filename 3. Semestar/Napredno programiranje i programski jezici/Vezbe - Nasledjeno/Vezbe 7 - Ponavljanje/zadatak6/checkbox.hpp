#ifndef CHECKBOX_HPP_INCLUDED
#define CHECKBOX_HPP_INCLUDED

class CheckBox : public Component {
private:
    bool pressed;
    static DinString typeName;
public:
    CheckBox () {
        X = 0;
        Y = 0;
        pressed = false;
    }

    CheckBox (double x, double y, bool p) {
        X = x;
        Y = y;
        pressed = p;
    }

    DinString getTypeName() const {
        return typeName;
    }

    void printComponent() const {
        cout << "Component: " << typeName << endl;
        Component::printComponent();
        cout << "Pressed? " << (pressed ? "YES" : "NO") << endl << endl;
    }

    void setPressed (bool press) {
        pressed = press;
    }

    bool getPressed () const {
        return pressed;
    }
};

DinString CheckBox::typeName = "CheckBox";

#endif // CHECKBOX_HPP_INCLUDED
