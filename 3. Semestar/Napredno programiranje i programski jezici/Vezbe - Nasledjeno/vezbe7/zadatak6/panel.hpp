#ifndef PANEL_HPP_INCLUDED
#define PANEL_HPP_INCLUDED

class Panel : public Component {
private:
    static DinString typeName;
    int capacity;
    List <Component*> components;
public:
    Panel () {
        this -> X = 0;
        this -> Y = 0;
        this -> capacity = 10;
    }

    Panel (const Panel& p) {
        this -> X = p.X;
        this -> Y = p.Y;
        this -> capacity = p.capacity;
        /// MOZEMO I SAMO OVO: components = p.components;  // klasa list ima operator dodele koji kopira jedan po jedan el
        components.clear();
        Component *comp;
        for (int i = 1; i <= p.components.size(); i++) {
            p.components.read(i, comp);
            components.add(i, comp);
        }
    }

    DinString getTypeName () const {
        return typeName;
    }

    void printComponent () const {
        cout << "-----------------" << endl;
        cout << "Component: " << typeName << endl;
        cout << " Kapacitet = " << capacity << " Broj komponenti: " << components.size() << endl;
        // MOGLI BISMO IMATI I PROVERU AKO IMAMO 0 KOMPONENTI
        Component::printComponent();
        Component *comp;
        for (int i = 1; i <= components.size(); i++) {
            components.read(i, comp);
            comp -> printComponent();
        }
        cout << "-----------------" << endl;
    }

    bool addComponent (Component& comp) {
        if (capacity > components.size()) {
            return components.add(components.size() + 1, &comp);
        }
        return false;
    }

    bool removeComponent (int position) {
        if (position > components.size() || position < 0) {
            return false;
        }
        return components.remove(position);
    }
};

DinString Panel::typeName = "Panel";

#endif // PANEL_HPP_INCLUDED
