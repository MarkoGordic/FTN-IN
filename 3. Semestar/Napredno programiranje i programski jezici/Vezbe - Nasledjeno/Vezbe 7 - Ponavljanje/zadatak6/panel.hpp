#ifndef PANEL_HPP_INCLUDED
#define PANEL_HPP_INCLUDED

class Panel : public Component {
private:
    static DinString typeName;
    int capacity;
    List <Component*> components;
public:
    Panel () {
        X = 0;
        Y = 0;
        capacity = 10;
    }

    Panel (const Panel& p) {
        X = p.X;
        Y = p.Y;
        capacity = p.capacity;
        components = p.components;
    }

    DinString getTypeName () const {
        return typeName;
    }

    void printComponent () const {
        cout << "----- " << typeName << " -----" << endl;
        cout << "Capacity: " << capacity << endl;
        Component* temp;
        for (int i = 1; i <= components.size(); i++){
            components.read(i, temp);
            temp->printComponent();
        }
    }

    void setCapacity (int cap) {
        capacity = cap;
    }

    int getCapacity () const {
        return capacity;
    }

    bool addComponent (Component& comp) {
        if (components.size() >= capacity)
            return false;
        return components.add(components.size() + 1, &comp);
    }

    bool removeComponent (int n) {
        return components.remove(n);
    }
};

DinString Panel::typeName = "Panel";

#endif // PANEL_HPP_INCLUDED
