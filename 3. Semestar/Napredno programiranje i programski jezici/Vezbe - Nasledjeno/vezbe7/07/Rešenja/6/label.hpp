#ifndef LABEL_HPP_INCLUDED
#define LABEL_HPP_INCLUDED

#include "component.hpp"

class Label : public Component {
    private:
        DinString text;
        static DinString typeName;

    public:
        Label(int X = 0, int Y = 0, const DinString& t = "") : text(t) {
            this -> X = X;
            this -> Y = Y;
        }

        DinString getTypeName() const {
            return typeName;
        }

        void printComponent() const {
            cout << getTypeName() << endl;
            Component::printComponent();
            cout << " Text = " << text;
        }

        DinString getText() const {
            return text;
        }

        void setText(const DinString& text) {
            this -> text = text;
        }
};


DinString Label::typeName = "Label";

#endif // LABEL_HPP_INCLUDED
