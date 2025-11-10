#include <iostream>
using namespace std;

#include "JSTrougao.hpp"

int main(){
    Trougao t1(1,4,4);
    JKTrougao jk1(2,3);
    JSTrougao js1(5);

    cout<<t1.getP()<<endl;
    cout<<jk1.getP()<<endl;
    cout<<js1.getP()<<endl;

    return 0;
}
