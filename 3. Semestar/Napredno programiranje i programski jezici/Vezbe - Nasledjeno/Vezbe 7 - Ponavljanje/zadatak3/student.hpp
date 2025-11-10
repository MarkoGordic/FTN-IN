#ifndef STUDENT_HPP_INCLUDED
#define STUDENT_HPP_INCLUDED

class Student : public Osoba {
private:
    int brojIndeksa;
public:
    Student() : Osoba(), brojIndeksa(17) {}

    Student(const Osoba& o, int br) : Osoba(o), brojIndeksa(br) {}

    Student(const DinString& i, const DinString& p, int br) : Osoba(i, p), brojIndeksa(br) {}

    Student(const Student& s) : Osoba(s.ime, s.prezime), brojIndeksa(s.brojIndeksa) {}

    void ispis() const {
        Osoba::ispis();
        cout << "I moj broj indeksa je " << brojIndeksa << "." << endl;
    }
};

#endif // STUDENT_HPP_INCLUDED
