#ifndef PANEL_HPP_INCLUDED
#define PANEL_HPP_INCLUDED

#include "component.hpp"
#include "list.hpp"


class Panel : public Component {
    private:
        static DinString typeName;
        List<Component*> components;
        int capacity;

    public:
        Panel() {
            X = 0;
            Y = 0;
            capacity = 10;
        }

        Panel (const Panel& p) {
            X = p.X;
            Y = p.Y;
            capacity = p.capacity;
            components = p.components;  // klasa list ima operator dodele koji kopira jedan po jedan el
        }

        DinString getTypeName() const {
            return typeName;
        }

        void printComponent() const {
            cout << getTypeName() << endl;
            Component::printComponent();
            cout << " Kapacitet = " << capacity << " Broj komponenti: " << components.size();
            if (components.size() > 0) {
                cout << " Komponente na panelu: " << endl;
                Component* c;
                for (int i = 1; i <= components.size(); i ++) {
                    components.read(i, c);
                    c -> printComponent();
                    cout << endl;
                }
            }
        }

        int getCapacity() const {
            return capacity;
        }

        void setCapacity(int capacity) {
            this -> capacity = capacity;
        }

        bool addComponent(Component& c) {
            if (components.size() == capacity)
                return false;

            return components.add(components.size() + 1, &c);
        }

        bool removeComponent(int position) {
            return components.remove(position);
        }
};

DinString Panel::typeName = "Panel";


#endif // PANEL_HPP_INCLUDED
