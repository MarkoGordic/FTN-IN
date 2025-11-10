#ifndef PHDSTUDENT_HPP_INCLUDED
#define PHDSTUDENT_HPP_INCLUDED

class PhDStudent : public Student {
private:
    double prosecnaOcena;
public:
    PhDStudent () : Student(), prosecnaOcena(10) {}
    PhDStudent (const char* i, const char* p, int bi, double po) : Student(i, p, bi), prosecnaOcena(po) {}
    PhDStudent (const DinString& i, const DinString& p, int bi, double po) : Student(i, p, bi), prosecnaOcena(po) {}
    PhDStudent (const Osoba& o, int bi, double po) : Student(o, bi), prosecnaOcena(po) {}
    PhDStudent (const Student& s, double po) : Student(s), prosecnaOcena(po) {}
    PhDStudent (const PhDStudent& s) : Student((Student)s), prosecnaOcena(s.prosecnaOcena) {}
    void predstaviSe () const {
        Student::predstaviSe(); // jer hocemo info kao da je student
        cout << "Prosecna ocena: " << prosecnaOcena << endl;
    }
};

#endif // PHDSTUDENT_HPP_INCLUDED
