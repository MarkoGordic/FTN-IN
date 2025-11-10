#ifndef STUDENT_HPP_INCLUDED
#define STUDENT_HPP_INCLUDED

class Student : public Osoba{
protected:
    int brojIndeksa;
public:
    Student () : Osoba(), brojIndeksa(17) {}
    Student (const char* i, const char* p, int bi) : Osoba(i, p), brojIndeksa(bi) {}
    Student (const DinString& i, const DinString& p, int bi) : Osoba(i, p), brojIndeksa(bi) {}
    Student (const Osoba& o, int bi) : Osoba(o), brojIndeksa(bi) {}
    Student (const Student& s) : Osoba((Osoba)s), brojIndeksa(s.brojIndeksa) {}
    void predstaviSe () const {
        Osoba::predstaviSe();                               // jer koristimo metodu iz osobe
        cout << "Broj indeksa: " << brojIndeksa << endl;
    }
};

#endif // STUDENT_HPP_INCLUDED
