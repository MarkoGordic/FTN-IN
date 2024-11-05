#include <iostream>

using namespace std;

#include "Oblik.hpp"

int main(){
    Oblik o1;
    cout << "Obim oblika o1: " << o1.obim() << endl;
    cout << "Povrsina oblika o1: " << o1.povrsina() << endl;

    Oblik o2(3,4);
    cout << "Obim oblika o2: " << o2.obim() << endl;
    cout << "Povrsina oblika o2: " << o2.povrsina() << endl;

    o2.setA(5);
    cout << "Obim oblika o2: " << o2.obim() << endl;
    cout << "Povrsina oblika o2: " << o2.povrsina() << endl;

    return 0;
}