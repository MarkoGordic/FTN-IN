#include <iostream>

using namespace std;

#include "Osoba.hpp"
#include "Student.hpp"
#include "PhDStudent.hpp"

int main(){
    Osoba o1("Pera", "Peric");
    Osoba o2(o1);
    Osoba o3("Mika", "Mikic");
    
    Student s1("Zika", "Zikic", 123);
    Student s2(s1);
    Student s3("Jova", "Jovic", 456);

    o1.predstaviSe();
    o2.predstaviSe();
    o3.predstaviSe();

    PhDStudent phd1("Mara", "Maric", 789, 9.5);
    PhDStudent phd2(phd1);
    PhDStudent phd3("Laza", "Lazic", 101112, 8.5);

    phd1.predstaviSe();
    phd2.predstaviSe();
    phd3.predstaviSe();

    return 0;
}