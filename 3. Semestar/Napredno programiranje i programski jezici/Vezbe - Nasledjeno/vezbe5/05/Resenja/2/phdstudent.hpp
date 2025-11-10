#ifndef PHDSTUDENT_DEF
#define PHDSTUDENT_DEF

#include "student.hpp"

class PhDStudent : public Student
{
    protected:
        double prosecnaOcena;

    public:
        PhDStudent(const char* s1 = "", const char* s2 = "", int i = 0, double po = 0) : Student(s1, s2, i), prosecnaOcena(po) { }

        PhDStudent(const DinString& ds1, const DinString& ds2, int i, double po) : Student(ds1, ds2, i), prosecnaOcena(po) { }

        PhDStudent(const Osoba& os, int i, double po) : Student(os, i), prosecnaOcena(po) { }

        PhDStudent(const Student& s, double po) : Student(s), prosecnaOcena(po) { }

        PhDStudent(const PhDStudent& phds) : Student((Student)phds), prosecnaOcena(phds.prosecnaOcena) { }

        void predstaviSe() const
        {
            Student::predstaviSe();
            cout << "Diplomirao sam sa prosecnom ocenom " << prosecnaOcena;
            cout << ", a sada sam student doktorskih studija" << endl;
        }
};

#endif
