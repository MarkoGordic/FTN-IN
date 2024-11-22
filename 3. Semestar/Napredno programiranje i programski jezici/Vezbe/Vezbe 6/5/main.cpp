#include <iostream>

using namespace std;

#include "Fotoaparat.hpp"

int main() {
    Fotoaparat<10> f;
    f.ukljuci();
    f.napuniFotoaparat(5);
    f.snimiFotografiju();
    f.snimiFotografiju();
    f.snimiFotografiju();
    f.punjenjeNaMax();
    f.iskljuci();

    return 0;
}