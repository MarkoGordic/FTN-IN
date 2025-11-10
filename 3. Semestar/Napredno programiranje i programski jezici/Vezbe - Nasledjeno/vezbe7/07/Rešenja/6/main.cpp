#include <iostream>
using namespace std;

#include "checkbox.hpp"
#include "label.hpp"
#include "panel.hpp"

int main()
{
    CheckBox cb1;
    cb1.printComponent();
    cout << endl << endl;

    CheckBox cb2(50, 70, true);
    cb2.printComponent();
    cout << endl << endl;

    Label lbl1;
    lbl1.printComponent();
    cout << endl << endl;

    Label lbl2(120, 30, "Volim programiranje: ");
    lbl2.printComponent();
    cout << endl << endl;


    Panel p1;
    p1.printComponent();
    cout << endl << endl;

    p1.setCapacity(3);
    p1.printComponent();
    cout << endl << endl;

    p1.addComponent(cb1);
    p1.addComponent(cb2);
    p1.addComponent(lbl1);

    p1.printComponent();
    cout << endl << endl;

    if (!p1.addComponent(lbl2))
        cout << "Greska prilikom dodavanja" << endl << endl;

    p1.removeComponent(1);
    p1.printComponent();
    cout << endl << endl;

    Panel p2(p1);
    p2.printComponent();
    cout << endl << endl;

   return 0;
}
