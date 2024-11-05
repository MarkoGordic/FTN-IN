#include <iostream>

using namespace std;

#include "Oblik.hpp"
#include "PravilanOblik.hpp"

int main(){
    Pravougaonik p1(5, 1);
    Elipsa e1(5, 1);

    Pravougaonik p2(5, 5);
    Elipsa e2(5, 5);

    Oblik o1 = Oblik(p1, e1);
    PravilanOblik po1 = PravilanOblik(p2, e2);
    cout << "Oblik: " << o1.obim() << " " << o1.povrsina() << endl;
    cout << "Pravilan oblik: " << po1.obim() << " " << po1.povrsina() << endl;

    return 0;
}