#include <iostream>

using namespace std;

#include "dinstring.hpp"
#include "list.hpp"
#include"component.hpp"
#include"checkbox.hpp"
#include "label.hpp"
#include "panel.hpp"

int main()
{
    CheckBox cb1, cb2(2,3,false);
    cb2.printComponent();

    Label l1, l2(5,6,"tekstic");
    l2.printComponent();

    Panel p1;
    p1.addComponent(cb1);
    p1.addComponent(cb2);

    p1.printComponent();
    return 0;
}
