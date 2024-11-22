#include <iostream>
#include "Artikal.hpp"
#include "dinstring.hpp"

using namespace std;

int main() {
    Artikal a1("Artikal 1", 100);
    Artikal a2("Artikal 2", 200);
    Artikal a3(a1);

    return 0;
}