#include <iostream>

using namespace std;

#include "student.hpp"

int main()
{
    Student s1;                             // konstruktor bez parametara
    Student s2(7.5, 17, 10, 75);            // konstruktor sa parametrima
    Student s3(s2);                         // konstruktor kopije

    cout << "Pre set: " << s2.getProsek() << endl;
    s2.setProsek(10.00);
    cout << "Nakon set: " << s2.getProsek() << endl << endl;

    s1.upisiOcenu(10);
    s1.upisiOcenu(9);
    s1.upisiOcenu(8);
    s1.upisiOcenu(10);
    return 0;
}
