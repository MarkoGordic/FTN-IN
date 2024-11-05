#ifndef STUDENT_HPP_INCLUDED
#define STUDENT_HPP_INCLUDED

#include "Osoba.hpp"

class Student : public Osoba {
protected:
    int brojIndeksa;
public:
    Student() : Osoba(), brojIndeksa(0) {}
    Student(const char* s1, const char* s2, int br) : Osoba(s1, s2), brojIndeksa(br) {}
    Student(const DinString& ds1, const DinString& ds2, int br) : Osoba(ds1, ds2), brojIndeksa(br) {}
    Student(const Osoba& o, int br) : Osoba(o), brojIndeksa(br) {}
    Student(const Student& s) : Osoba(s), brojIndeksa(s.brojIndeksa) {}

    void predstaviSe() const {
        cout << "Ja sam student " << ime << " " << prezime << " sa brojem indeksa " << brojIndeksa << endl;
    }
};

#endif // STUDENT_HPP_INCLUDED