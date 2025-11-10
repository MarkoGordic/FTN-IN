#include <iostream>

using namespace std;

#include "dinstring.hpp"
#include "artikal.hpp"

int main()
{
    DinString str("ijaoj");
    Artikal a2("joj", 56), a3(str, 6);
    cout << a2 << endl;
    {
        Artikal a4(":", 476);
        cout << a4 << endl;
    }
    cout << a2 << endl;
    return 0;
}
