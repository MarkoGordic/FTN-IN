#ifndef LABEL_HPP_INCLUDED
#define LABEL_HPP_INCLUDED

class Label : public Component {
private:
    DinString text;
    static DinString typeName;
public:
    Label () : text() {
        X = 0;
        Y = 0;
    }

    Label (double x, double y, const DinString& txt) : text(txt) {
        X = x;
        Y = y;
    }

    DinString getTypeName() const {
        return typeName;
    }

    void printComponent() const {
        cout << "Component: " << typeName << endl;
        Component::printComponent();
        cout << "\"" << text << "\"" << endl << endl;
    }

    void setText (const DinString& txt) {
        text = txt;
    }

    DinString getText () const {
        return text;
    }
};

DinString Label::typeName = "Label";

#endif // LABEL_HPP_INCLUDED
