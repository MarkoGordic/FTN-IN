#include <iostream>

using namespace std;

#include "dinstring.hpp"
#include "list.hpp"
#include "component.hpp"
#include "checkbox.hpp"
#include "label.hpp"
#include "panel.hpp"

int main()
{
    CheckBox cb1, cb2(3, 4, false), cb3(5, 7, true);
    cout << "TESTIRANJE " << cb1.getTypeName() << endl;
    cout << cb2.getPressed() << endl;
    cb2.setPressed(true);
    cout << cb2.getPressed() << endl;
    cb2.printComponent();

    DinString d("Mile");
    Label l1, l2(5, 8, "Marija"), l3(2, 3, "Nenad"), l4(4, 6, d), l5(5, 5, "HJOJ");
    cout << endl << "TESTIRANJE " << l1.getTypeName() << endl;
    cout << l5.getText() << endl;
    l5.setText(d);
    cout << l5.getText() << endl;
    l2.printComponent();

    Panel p1;
    cout << endl << "TESTIRANJE " << p1.getTypeName() << endl;
    p1.addComponent(cb2);
    p1.addComponent(cb3);
    p1.addComponent(l5);
    p1.printComponent();
    Panel p2(p1);
    p2.addComponent(l2);
    p2.addComponent(l3);
    p2.printComponent();
    p1.printComponent();

    p2.removeComponent(1);
    p2.removeComponent(1);
    p2.removeComponent(1);
    p2.removeComponent(1);
    p2.removeComponent(-1);
    p2.removeComponent(2);
    p2.printComponent();
    return 0;
}
