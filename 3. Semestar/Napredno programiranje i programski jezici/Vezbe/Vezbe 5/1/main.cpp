#include <iostream>

using namespace std;

#include "Trougao.hpp"
#include "JKTrougao.hpp"
#include "JSTrougao.hpp"

int main(){
    Trougao t1;
    cout << "Obim trougla t1: " << t1.obim() << endl;
    cout << "Povrsina trougla t1: " << t1.povrsina() << endl;

    JKTrougao jkt1;
    cout << "Obim trougla jkt1: " << jkt1.obim() << endl;
    cout << "Povrsina trougla jkt1: " << jkt1.povrsina() << endl;

    JKTrougao jkt2(3,4);
    cout << "Obim trougla jkt2: " << jkt2.obim() << endl;
    cout << "Povrsina trougla jkt2: " << jkt2.povrsina() << endl;

    jkt2.setB(5);
    cout << "Obim trougla jkt2: " << jkt2.obim() << endl;
    cout << "Povrsina trougla jkt2: " << jkt2.povrsina() << endl;

    JSTrougao jst1;
    cout << "Obim trougla jst1: " << jst1.obim() << endl;
    cout << "Povrsina trougla jst1: " << jst1.povrsina() << endl;
    cout << "A: " << jst1.getA() << ", B: " << jst1.getB() << ", C: " << jst1.getC() << endl;

    return 0;
}