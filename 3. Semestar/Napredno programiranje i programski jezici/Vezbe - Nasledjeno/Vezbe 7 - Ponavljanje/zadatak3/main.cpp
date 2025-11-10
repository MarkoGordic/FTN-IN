#include <iostream>

using namespace std;

#include "dinstring.hpp"
#include "list.hpp"
#include "osoba.hpp"
#include "student.hpp"
#include "profesor.hpp"
#include "ucionica.hpp"

int main()
{
    Osoba o1;
    Student s1;
    Ucionica u1;
    u1.dodajOsobu(o1);
    u1.dodajOsobu(s1);
    u1.ispis();
    return 0;
}
