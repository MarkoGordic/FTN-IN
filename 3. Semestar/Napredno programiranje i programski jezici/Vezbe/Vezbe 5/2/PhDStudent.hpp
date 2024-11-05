#ifndef PHDSTUDENT_HPP_INCLUDED
#define PHDSTUDENT_HPP_INCLUDED

#include "Student.hpp"

class PhDStudent : public Student {
private:
    double prosecnaOcena;
public:
    PhDStudent() : Student(), prosecnaOcena(0) {}
    PhDStudent(const char* s1, const char* s2, int br, double po) : Student(s1, s2, br), prosecnaOcena(po) {}
    PhDStudent(const DinString& ds1, const DinString& ds2, int br, double po) : Student(ds1, ds2, br), prosecnaOcena(po) {}
    PhDStudent(const Osoba& o, int br, double po) : Student(o, br), prosecnaOcena(po) {}
    PhDStudent(const Student& s, double po) : Student(s), prosecnaOcena(po) {}
    PhDStudent(const PhDStudent& phds) : Student(phds), prosecnaOcena(phds.prosecnaOcena) {}

    void predstaviSe() const {
        cout << "Ja sam PhD student " << ime << " " << prezime << " sa brojem indeksa " << brojIndeksa << " i prosekom " << prosecnaOcena << endl;
    }
};

#endif // PHDSTUDENT_HPP_INCLUDED