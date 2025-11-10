#ifndef LABEL_HPP_INCLUDED
#define LABEL_HPP_INCLUDED

class Label : public Component {
private:
    DinString text;
    static DinString typeName;
public:
    Label () {
        this -> X = 0;
        this -> Y = 0;
        this -> text = "";
    }

    Label (double X, double Y, const DinString& text) {
        this -> X = X;
        this -> Y = Y;
        this -> text = text;
    }

    Label (double X, double Y, const char* txt) : text(txt) {
        this -> X = X;
        this -> Y = Y;
    }

    DinString getTypeName() const {
        return typeName;
    }

    DinString getText () const {
        return text;
    }

    void setText (const DinString& txt) {
        text = txt;
    }

    void printComponent () const {
        cout << "Component: " << typeName << endl;
        Component::printComponent();
        cout << "Text: " << text << endl;
    }
};

DinString Label::typeName = "Label";

#endif // LABEL_HPP_INCLUDED
