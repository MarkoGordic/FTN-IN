#include "student.hpp"
#include <iostream>
using namespace std;

// primer implementacije konstruktora i metoda
// u ovom slucaju konstruktor: Student::Student(...){}
// dok metoda ide: tip Student::metoda(...){}

Student::Student(){
    prosek = 0;
    brojIndeksa = 1;
    brojOcena = 0;
    zbirOcena = 0;
}

Student::Student(double p, int bi, int bo, int zo){
    prosek = p;
    brojIndeksa = bi;
    brojOcena = bo;
    zbirOcena = zo;
}

Student::Student(const Student& student){
    prosek = student.prosek;
    brojIndeksa = student.brojIndeksa;
    brojOcena = student.brojOcena;
    zbirOcena = student.zbirOcena;
}

double Student::getProsek() const {
    return prosek;
}

void Student::setProsek(double p){
    prosek = p;
}

void Student::upisiOcenu(int ocena){
    zbirOcena += ocena;
    brojOcena++;
    prosek = (double)zbirOcena / brojOcena;
    cout << "Upisujem ocenu: " << ocena << endl;
    cout << "Novi prosek: " << prosek << endl;
}
